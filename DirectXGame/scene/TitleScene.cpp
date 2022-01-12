#include "TitleScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>
#include <thread>

using namespace DirectX;

// 非同期ロード用
ModelManager* modelMngTitle = ModelManager::GetInstance();
bool isLoadedTitle = false;
std::mutex isLoadedMutexTitle;

// 非同期ロード用
void SetLockFlag(bool _)
{
	std::lock_guard<std::mutex>  lock(isLoadedMutexTitle);
	isLoadedTitle = true;
}

bool GetLockFlag()
{
	std::lock_guard<std::mutex>  lock(isLoadedMutexTitle);
	return isLoadedTitle;
}

// 非同期ロード関数
void AsyncLoad()
{
	//ダミーで10秒待つ
	/*auto sleepTime = std::chrono::seconds(10);
	std::this_thread::sleep_for(sleepTime);*/

	modelMngTitle->Load(13, "01_77");	// 13
	modelMngTitle->Load(33, "02_41");	// 33
	modelMngTitle->Load(53, "03_40");	// 53
	modelMngTitle->Load(73, "04_85");	// 73

	SetLockFlag(true);
}

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
	safe_delete(tmpSprite);
}

void TitleScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptrチェック
	BaseScene::Initialize(dxCommon, input, audio);

	// 汎用的初期化
	{
		// カメラ生成
		camera = new DebugCamera(WinApp::window_width, WinApp::window_height, input);

		// 3Dオブジェクトにカメラをセット
		Object3d::SetCamera(camera);

		// デバッグテキスト用テクスチャ読み込み
		if (!Sprite::LoadTexture(texNumber, L"Resources/debugfont.png")) {
			assert(0);
			return;
		}
		// デバッグテキスト初期化
		text = Text::GetInstance();
		text->Initialize(texNumber);

		// ライト生成
		lightGroup = LightGroup::Create();
		// 3Dオブエクトにライトをセット
		Object3d::SetLightGroup(lightGroup);

		// デバイスをセット
		Fbx::SetDevice(dxCommon->GetDevice());
		// カメラをセット
		Fbx::SetCamera(camera);
		// グラフィックスパイプライン生成
		Fbx::CreateGraphicsPipeline();

		// パーティクルマネージャ生成
		particleMan = ParticleManager::GetInstance();
		particleMan->SetCamera(camera);

		// 非同期ロード用
		auto count = std::thread::hardware_concurrency();
		if (count < 3)
		{
			assert(1);
		}
	}

	// スプライト初期設定
	{
		// スプライト用テクスチャ読み込み
		{
			Sprite::LoadTexture(1, L"Resources/texture/title_tmp.png");
		}

		// スプライト生成
		{
			tmpSprite = Sprite::Create(1, { 0,0 });
		}

		// スプライト初期設定
		{
		}
	}

	// 非同期ロード開始
	if (!isLoadedTitle)
	{
		th = new std::thread(AsyncLoad);
	}

	// カメラ注視点をセット
	camera->SetTarget({ 0, -1, 0 });
	camera->SetDistance(25.0f);

}

void TitleScene::Update()
{
	// コントローラの更新
	xinput.Update();
	
	// 非同期ロード中
	if (!GetLockFlag())
	{

	}
	else   // ロード終了後
	{
		// SPACEで次のシーン
		if (input->TriggerKey(DIK_SPACE))
		{
			nextScene = new SelectScene();
		}
	}

	// ESCAPEでゲーム終了
	if (input->PushKey(DIK_ESCAPE))
	{
		TitleScene::~TitleScene();
		PostQuitMessage(0);
	}

	// マウスポイント
	{
		static POINT p;
		GetCursorPos(&p);
		WinApp* win = nullptr;
		win = new WinApp();
		ScreenToClient(FindWindowA(nullptr, "Hooper"), &p);
		mousePos = { (float)p.x, (float)p.y };
	}

	// パーティクル生成
	//CreateParticles();

	lightGroup->Update();
	camera->Update();
	particleMan->Update();

	// 3Dオブジェクト更新
	{
	}
}

void TitleScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	// 背景スプライト描画
	{
		Sprite::PreDraw(cmdList);
		{
			tmpSprite->Draw();
		}
		Sprite::PostDraw();

		// 深度バッファクリア
		dxCommon->ClearDepthBuffer();
	}

	// 3Dオブジェクト描画
	{
		Object3d::PreDraw(cmdList);
		{
			
		}
		Object3d::PostDraw();

		// パーティクルの描画
		particleMan->Draw(cmdList);
	}

	// 前景スプライト描画
	{
		Sprite::PreDraw(cmdList);
		{

			// デバッグテキストの描画
			text->DrawAll(cmdList);
		}
		Sprite::PostDraw();
	}

	// ImGui描画
	{
		/*ImGui::Begin("OPTION");
		ImGui::SetWindowSize(ImVec2(100, 100));
		ImGui::SliderFloat("感度", &sence, 0.01f, 5.0f);
		ImGui::End();*/
	}
}

void TitleScene::Finalize()
{
	if (!isLoadedTitle)
	{
		th->join();
	}
}
