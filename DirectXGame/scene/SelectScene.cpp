#include "SelectScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>

using namespace DirectX;
using namespace SpriteData;

SelectScene::SelectScene()
{
}

SelectScene::~SelectScene()
{
	for (auto x : map)
	{
		delete x;
	}
	delete back;
}

void SelectScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptrチェック
	BaseScene::Initialize(dxCommon, input, audio);

	// 汎用的初期化
	{
		// カメラ生成
		camera = new FixedCamera(WinApp::window_width, WinApp::window_height);
		
		// デバイスをセット
		Fbx::SetDevice(dxCommon->GetDevice());
		// カメラをセット
		Fbx::SetCamera(camera);
		// グラフィックスパイプライン生成
		Fbx::CreateGraphicsPipeline();
	}

	// スプライト初期設定
	{
		// スプライト用テクスチャ読み込み
		{
			// ロードしていないならする
			if (!SpriteLoader::GetSelectFlag())
			{
				SpriteLoader::LoadSelectSprite();
			}
		}

		// スプライト生成
		{
		}

		// スプライト初期設定
		{
		}
	}

	// FBXオブジェクト初期設定
	{
		// セレクト用マップ
		for (int i = 0; i < 4; i++)
		{
			map[i] = new Fbx();
			map[i]->Initialize();
			map[i]->SetModel(ModelManager::GetInstance()->GetModel(i + stageData->GetDeSelectData().firstNum + 1));
			map[i]->SetFog(false);
		}

		// 背景
		back = new Fbx();
		back->Initialize();
		back->SetModel(ModelManager::GetInstance()->GetModel(stageData->GetDeSelectData().firstNum));
		back->SetFog(false);
		back->SetPosition({ 0,0,300 });
		back->SetScale({ 5,5,8 });
	}

	// カメラ初期化
	{
		// カメラ注視点をセット
		camera->SetTarget({ 0, 10, 0 });
		camera->SetEye({ 0,200,400 });
	}

	// 各クラスの初期化
	{
	}

	isGodray = true;
}

void SelectScene::Update()
{
	stop = false;

	if (!stop)
	{
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
	camera->Update();

	// 3Dオブジェクト更新
	{
		for (int i = 0; i < 4; i++)
		{
			map[i]->Update();
		}

		back->Update();
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

		// スプライト描画後処理
		Sprite::PostDraw();
		// 深度バッファクリア
		dxCommon->ClearDepthBuffer();
	}

	// 3D描画
	{
		back->Draw(cmdList);

		for (int i = 0; i < 4; i++)
		{
			map[i]->Draw(cmdList);
		}
	}

	// 前景スプライト描画
	{
		// 前景スプライト描画前処理
		Sprite::PreDraw(cmdList);

		// スプライト描画後処理
		Sprite::PostDraw();
	}
}

void SelectScene::Finalize()
{
}
