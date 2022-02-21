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
	safe_delete(camera);
	for (auto x : map)
	{
		safe_delete(x);
	}
	delete back;
	for (auto x : gush)
	{
		safe_delete(x);
	}
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
			map[i]->SetModel(ModelManager::GetInstance()->GetModel(i + stageData->GetDeSelectData().firstNum + 2));
			map[i]->SetFogColor({ 0.01f, 0.01f, 0.01f, 1.0f });
		}

		// 背景
		back = new Fbx();
		back->Initialize({0,1,0});
		back->SetModel(ModelManager::GetInstance()->GetModel(stageData->GetDeSelectData().firstNum));
		back->SetFog(false);
		back->SetPosition({ 0,0,300 });
		back->SetScale({ 5,5,6 });
		back->SetRotation({ 0,0,180 });
	}

	// カメラ初期化
	{
		// カメラ注視点をセット
		camera->SetTarget({ 0, -50, 0 });
		camera->SetEye({ 0,250,500 });
	}

	// 各クラスの初期化
	{
		for (int i = 0; i < gush.size(); i++)
		{
			gush[i] = new Gush();
			gush[i]->Initialize();
			gush[i]->SetPlayerPos({ 0,250,500 });
			gush[i]->SetMax(260);
			gush[i]->SetDis({ 240, 250 });
			gush[i]->SetSpeed(0.01f);
		}
	}

	isGodray = false;
	trans = 1;
}

void SelectScene::Update()
{
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

	// セレクトマップ回転指定
	{
		// 回転スタート
		if (input->TriggerKey(DIK_LEFT) && !isMove)
		{
			map[nowMap]->SetScale({ 1, 1, 1});
			nowMap--;
			vel = 1;
			isMove = true;
			// 回転終着点決定
			reRot = rad + 90 * vel;
			selRad = 0.0f;
		}
		if (input->TriggerKey(DIK_RIGHT) && !isMove)
		{
			map[nowMap]->SetScale({ 1, 1, 1 });
			nowMap++;
			vel = -1;
			isMove = true;
			// 回転終着点決定
			reRot = rad + 90 * vel;
			selRad = 0.0f;
		}

		// 回転中
		if (isMove)
		{
			// 回転
			rad += 1.5f * vel;

			// 一定で止まる
			if ((vel == 1 && reRot < rad) || (vel == -1 && rad < reRot))
			{
				vel = 0;
				rad = reRot;
				isMove = false;
			}
		}

		// 数字ループ
		if (nowMap == 4)
		{
			nowMap = 0;
		}
		if (nowMap == -1)
		{
			nowMap = 3;
		}
	}

	// 選択中のマップの挙動
	if (!isMove)
	{
		// 基本暗く
		for (auto x : map)
		{
			x->SetFog(true);
		}

		// 明るくする
		map[nowMap]->SetFog(false);

		// ちょっと大きくする
		map[nowMap]->SetScale({ 1.5f, 1.5f, 1.5f });

		// 回転させる
		map[nowMap]->SetRotation({ map[nowMap]->GetRotation().x, 
								   map[nowMap]->GetRotation().y + 0.5f, 
								   map[nowMap]->GetRotation().z });

		// 上下させる
		selRad += 0.03f;
		XMFLOAT3 tmpPos = map[nowMap]->GetPosition();
		map[nowMap]->SetPosition({ tmpPos.x, sinf(selRad) * 25.0f, tmpPos.z });

		// シーン移行
		if (input->TriggerKey(DIK_SPACE))
		{
			// 選択したマップでゲームシーンへ
			nextScene = new LoadScene(nowMap);
		}
	}

	// 3Dオブジェクト更新
	{
		for (int i = 0; i < 4; i++)
		{
			// 現在の全体ラジアン
			float radian = (rad + 90.0f * (float)i + 180.0f) * 3.14f / 180.0f;

			map[i]->Update();
			map[i]->SetPosition({ (float)sinf(radian) * 200, 0, -(float)cosf(radian) * 200 });
		}

		back->Update();
	}

	// 各クラスの更新
	{
		camera->Update();
		for (auto x : gush)
		{
			x->Update();
		}
	}

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

		for (auto x : map)
		{
			x->Draw(cmdList);
		}

		for (auto x : gush)
		{
			x->Draw(cmdList);
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
