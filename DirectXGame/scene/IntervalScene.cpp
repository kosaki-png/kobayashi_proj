#include "IntervalScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>

using namespace DirectX;

// 非同期ロード用
bool isLoaded = false;
std::mutex isLoadedMutex;
// モデル管理クラスのインスタンス取得
ModelManager* modelMng = ModelManager::GetInstance();

// 非同期ロード用
void SetLockFlag(bool _)
{
	std::lock_guard<std::mutex>  lock(isLoadedMutex);
	isLoaded = true;
}

bool GetLockFlag()
{
	std::lock_guard<std::mutex>  lock(isLoadedMutex);
	return isLoaded;
}

// 非同期ロード関数
void AsyncLoad()
{
	//ダミーで10秒待つ
	/*auto sleepTime = std::chrono::seconds(10);
	std::this_thread::sleep_for(sleepTime);*/

	modelMng->Load("player");	// 0
	modelMng->Load("01_87");	// 1
	modelMng->Load("01_88");	// 2
	modelMng->Load("01_89");	// 3
	modelMng->Load("01_77");	// 4
	modelMng->Load("01_78");	// 5
	modelMng->Load("01_79");	// 6
	modelMng->Load("01_67");	// 7
	modelMng->Load("01_68");	// 8
	modelMng->Load("01_69");	// 9
	modelMng->Load("floor");	// 10
	modelMng->Load("skydome");	// 11
	//modelMng->Load("player");	// 1
	//modelMng->Load("player");	// 2
	//modelMng->Load("player");	// 3
	//modelMng->Load("player");	// 4
	//modelMng->Load("player");	// 5
	//modelMng->Load("player");	// 6
	//modelMng->Load("player");	// 7
	//modelMng->Load("player");	// 8
	//modelMng->Load("player");	// 9
	//modelMng->Load("player");	// 10
	//modelMng->Load("player");	// 11

	SetLockFlag(true);
}

IntervalScene::IntervalScene()
{
}

IntervalScene::~IntervalScene()
{
}

void IntervalScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
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
			Sprite::LoadTexture(1, L"Resources/texture/load.png");
			Sprite::LoadTexture(2, L"Resources/texture/loaded.png");
		}

		// スプライト生成
		{
			load = Sprite::Create(1, { 0,0 });
			loadCircle = Sprite::Create(2, { 0,0 });
		}

		// スプライト初期設定
		{
		}
	}

	// 非同期ロード開始
	if (!isLoaded)
	{
		th = new std::thread(AsyncLoad);
	}
}

void IntervalScene::Update()
{
	// 非同期ロード中
	if (!GetLockFlag())
	{
		
	}
	else   // ロード終了後
	{
		// SPACEで次のシーン
		if (input->TriggerKey(DIK_SPACE))
		{
			nextScene = new GameScene();
		}
	}

	lightGroup->Update();
	particleMan->Update();
}

void IntervalScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	// 背景スプライト描画
	{
		Sprite::PreDraw(cmdList);
		{

		}
		Sprite::PostDraw();

		// 深度バッファクリア
		dxCommon->ClearDepthBuffer();
	}

	// 3Dオブジェクト描画
	{
		Object3d::PreDraw(cmdList);
		{
			// 非同期ロード中
			if (!GetLockFlag())
			{

			}
			else   // ロード終了後
			{

			}
		}
		Object3d::PostDraw();

		// パーティクルの描画
		particleMan->Draw(cmdList);
	}

	// 前景スプライト描画
	{
		Sprite::PreDraw(cmdList);
		{
			// 非同期ロード中
			if (!GetLockFlag())
			{
				load->Draw();
			}
			else   // ロード終了後
			{
				loadCircle->Draw();
			}

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

void IntervalScene::Finalize()
{
	if (!isLoaded)
	{
		th->join();
	}
}
