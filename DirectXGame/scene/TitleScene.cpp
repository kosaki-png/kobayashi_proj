#include "TitleScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>
#include <thread>

using namespace DirectX;

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

	// OBJオブジェクト初期設定
	{
		// モデル読み込み
		{
		}

		// 3Dオブジェクト生成
		{
		}

		// 3Dオブジェクト初期設定
		{
		}
	}

	// FBXオブジェクト初期設定
	{
		// モデル読み込み
		{
		}

		// 3Dオブジェクト生成
		{
		}

		// 3Dオブジェクト初期設定
		{
		}
	}

	// カメラ注視点をセット
	camera->SetTarget({ 0, -1, 0 });
	camera->SetDistance(25.0f);

	fade->Initialize();

	// 
	if (!nextSceneFlag)
	{

	}
	
	/*texCollision = new TexCollision();
	texCollision->LoadTexture(1, L"Resources/texture/test.png");
	static XMFLOAT4 testColor;
	testColor = texCollision->GetPixelColor(1, 1, 0);

	assert(1);*/
}

void TitleScene::Update()
{
	// コントローラの更新
	xinput.Update();
	stop = false;
	if (!stop)
	{
		// スペースで指定のシーンへ
		if (input->TriggerKey(DIK_SPACE) || xinput.TriggerButtom(0, xinput_A))
		{
			/*fade->InStart(false);
			nextSceneFlag = true;*/
			// セレクトシーンへ
			nextScene = new SelectScene();
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

		// 
		if (input->TriggerKey(DIK_1))
		{
			fade->InStart();
		}
		if (input->TriggerKey(DIK_2))
		{
			fade->OutStart();
		}
	}

	fade->Update();

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
		// 背景スプライト描画前処理
		Sprite::PreDraw(cmdList);

		/// <summary>
		/// ここに背景スプライトの描画処理を追加
		/// </summary>
		tmpSprite->Draw();
		
		// スプライト描画後処理
		Sprite::PostDraw();
		// 深度バッファクリア
		dxCommon->ClearDepthBuffer();
	}

	// 3D描画
	{
		// 3Dオブジェクトの描画
		Object3d::PreDraw(cmdList);

		/// <summary>
		/// ここに3Dオブジェクトの描画処理を追加
		/// </summary>

		Object3d::PostDraw();

		// パーティクルの描画
		particleMan->Draw(cmdList);
	}

	// 前景スプライト描画
	{
		// 前景スプライト描画前処理
		Sprite::PreDraw(cmdList);

		/// <summary>
		/// ここに前景スプライトの描画処理を追加
		/// </summary>
		
		// デバッグテキストの描画
		text->DrawAll(cmdList);

		fade->Draw();

		// スプライト描画後処理
		Sprite::PostDraw();
	}
}

void TitleScene::Finalize()
{
}
