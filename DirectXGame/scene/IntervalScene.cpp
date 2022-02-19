#include "IntervalScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>

using namespace DirectX;
using namespace SpriteData;

IntervalScene::IntervalScene()
{
}

IntervalScene::~IntervalScene()
{
	safe_delete(camera);
	safe_delete(transition);
}

void IntervalScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptrチェック
	BaseScene::Initialize(dxCommon, input, audio);

	// 汎用的初期化
	{
		// カメラ生成
		camera = new OrbitCamera(WinApp::window_width, WinApp::window_height);

		// デバイスをセット
		Fbx::SetDevice(dxCommon->GetDevice());
		// カメラをセット
		Fbx::SetCamera(camera);
		// グラフィックスパイプライン生成
		Fbx::CreateGraphicsPipeline();

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
			// ロードしていないならする
			if (!SpriteLoader::GetIntervalFlag())
			{
				SpriteLoader::LoadIntervalSprite();
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
		
	}

	// カメラ初期設定
	{
		//camera->SetMouseFlag(false);
	}

	// 各クラス初期化
	{
		transition = new Extend();
		//transition = new Gradually(false);
		transition->Initialize();
	}
}

void IntervalScene::Update()
{
	transition->Update();

	// カメラ更新
	{
		camera->Update();
	}
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
	}

	// 前景スプライト描画
	{
		Sprite::PreDraw(cmdList);
		{
			transition->Draw();
		}
		Sprite::PostDraw();
	}
}

void IntervalScene::Finalize()
{
}

void IntervalScene::Start()
{
	transition->Start();
}