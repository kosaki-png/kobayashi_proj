#include "EndScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>

using namespace DirectX;
using namespace SpriteData;

EndScene::EndScene()
{
}

EndScene::~EndScene()
{
	safe_delete(camera);
	safe_delete(tmpSprite);
	safe_delete(frame);
	safe_delete(cursor);
}

void EndScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptrチェック
	BaseScene::Initialize(dxCommon, input, audio);

	// カメラ生成
	camera = new OrbitCamera(WinApp::window_width, WinApp::window_height);

	// スプライト初期設定
	{
		// スプライト用テクスチャ読み込み
		{
			// ロードしていないならする
			if (!SpriteLoader::GetEndFlag())
			{
				SpriteLoader::LoadEndSprite();
			}
		}

		// スプライト生成
		{
			tmpSprite = Sprite::Create(CLEAR, { 0,0 });
			frame = Sprite::Create(RESULT_FRAME, { 0,0 });
			cursor = Sprite::Create(RESULT_CURSOR, { 0,0 });
		}

		// スプライト初期設定
		{
			cursor->SetAnchorPoint({ 0.5f, 0.5f });
			cursor->SetPosition({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 });
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
	camera->SetTarget({ 0, 1, 0 });

	isGodray = true;
	trans = 0;
}

void EndScene::Update()
{
	// マウスポイント
	{
		static POINT p;
		GetCursorPos(&p);
		WinApp* win = nullptr;
		win = new WinApp();
		ScreenToClient(FindWindowA(nullptr, "Hooper"), &p);
		mousePos = { (float)p.x, (float)p.y };
	}

	if (cursorFlip)
	{
		// カーソル移動（キー）
		if (input->TriggerKey(DIK_LEFT) || input->TriggerKey(DIK_A))
		{
			cursorFlip = false;
			cursor->SetIsFlipX(cursorFlip);
		}

		// スペースで指定のシーンへ
		if (input->TriggerKey(DIK_SPACE))
		{
			// タイトルシーンへ
			nextScene = new TitleScene();
		}
	}
	else
	{
		// カーソル移動（キー）
		if (input->TriggerKey(DIK_RIGHT) || input->TriggerKey(DIK_D))
		{
			cursorFlip = true;
			cursor->SetIsFlipX(cursorFlip);
		}

		// スペースで指定のシーンへ
		if (input->TriggerKey(DIK_SPACE))
		{
			// セレクトシーンへ
			nextScene = new SelectScene();
		}
	}

	camera->Update();

	// 3Dオブジェクト更新
	{
	}
}

void EndScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	// 背景スプライト描画
	{
		// 背景スプライト描画
		Sprite::PreDraw(cmdList);
		{
			tmpSprite->Draw();
		}
		Sprite::PostDraw();

		// 深度バッファのクリア
		dxCommon->ClearDepthBuffer();
	}

	// 3D描画
	{
	}

	// 前景スプライト描画
	{
		// 前景スプライト描画
		Sprite::PreDraw(cmdList);
		{

		}
		Sprite::PostDraw();
	}
}

void EndScene::FrontDraw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	// スプライト描画
	Sprite::PreDraw(cmdList);
	{
		frame->Draw();
		cursor->Draw();
	}
	Sprite::PostDraw();
}

void EndScene::Finalize()
{
}
