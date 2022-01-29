#include "SelectScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>

using namespace DirectX;

SelectScene::SelectScene()
{
}

SelectScene::~SelectScene()
{
	safe_delete(tmpSprite);
}

void SelectScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptrチェック
	BaseScene::Initialize(dxCommon, input, audio);

	// 汎用的初期化
	{
		// カメラ生成
		camera = new MainCamera(WinApp::window_width, WinApp::window_height, input);

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

		// パーティクルマネージャ生成
		particleMan = ParticleManager::GetInstance();
		particleMan->SetCamera(camera);
	}

	// スプライト初期設定
	{
		// スプライト用テクスチャ読み込み
		{
			Sprite::LoadTexture(1, L"Resources/texture/star.png");
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
		// モデル生成
		{
			for (int i = 0; i < 4; i++)
			{
				map[i] = new Fbx();
				map[i]->Initialize();
				map[i]->SetModel(ModelManager::GetInstance()->GetModel(i * 20 + 13));
			}
		}
	}

	// カメラ注視点をセット
	camera->SetTarget({ 0, 1, 0 });
	//camera->SetDistance(10.0f);

	// 各クラスの初期化
	{
	}
}

void SelectScene::Update()
{
	stop = false;

	if (!stop)
	{
		// コントローラの更新
		xinput.Update();

		// シーン移行
		if (input->TriggerKey(DIK_0))
		{
			// 選択したマップでゲームシーンへ
			nextScene = new LoadScene(0);
		}
		if (input->TriggerKey(DIK_1))
		{
			// 選択したマップでゲームシーンへ
			nextScene = new LoadScene(1);
		}
		if (input->TriggerKey(DIK_2))
		{
			// 選択したマップでゲームシーンへ
			nextScene = new LoadScene(2);
		}
		if (input->TriggerKey(DIK_3))
		{
			// 選択したマップでゲームシーンへ
			nextScene = new LoadScene(3);
		}

		// ESCAPEでゲーム終了
		if (input->PushKey(DIK_ESCAPE))
		{
			SelectScene::~SelectScene();
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
	}

	lightGroup->Update();
	camera->Update();
	particleMan->Update();

	// 3Dオブジェクト更新
	{
		for (int i = 0; i < 4; i++)
		{
			map[i]->Update();
		}
	}

	// 各クラスの更新
	{}

}

void SelectScene::Draw()
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
		for (int i = 0; i < 4; i++)
		{
			map[i]->Draw(cmdList, true);
		}

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

		// スプライト描画後処理
		Sprite::PostDraw();
	}
}

void SelectScene::Finalize()
{
}
