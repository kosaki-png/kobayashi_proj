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
	safe_delete(line[0].sprite);
	safe_delete(line[1].sprite);
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
			for (int i = 0; i < 2; i++)
			{
				// 初期位置設定
				line[i].sprite = Sprite::Create(INTERVAL, { 0,0 });
				line[i].size = { 3000, 10 };
				line[i].position = { -3000, WINDOW_HEIGHT / 2 - 5 };
				line[i].speed = { 70.0f, 0 };
			}
			
			line[1].sprite->SetAnchorPoint({ 0.0f, 1.0f });
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
}

void IntervalScene::Update()
{
	isCover = false;

	if (isEffect)
	{
		// エフェクト終了
		if (startCnt > 180)
		{
			isEffect = false;
		}

		for (int i = 0; i < 2; i++)
		{
			if (startCnt >= 30 && startCnt < 90)
			{
				if (line[i].position.x <= WINDOW_WIDTH - 3000)
				{
					line[i].position.x += line[i].speed.x;
					line[i].position.y += line[i].speed.y;
				}
				if (line[i].position.x >= WINDOW_WIDTH - 3000)
				{
					if (width < WINDOW_HEIGHT / 2)
					{
						width += width / 8;
					}

					line[i].size = { 3000, width };
				}
			}
			if (startCnt >= 120)
			{
				if (width > 0)
				{
					width -= width / 8;
				}
				if (width <= 0)
				{
					width = 0;
				}
				line[i].size = { 3000, width };
			}

			if (startCnt == 90)
			{
				isCover = true;
			}
			line[i].sprite->SetPosition(line[i].position);
			line[i].sprite->SetSize(line[i].size);
		}
	}

	// カメラ更新
	{
		camera->Update();
	}

	startCnt++;
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
			if (isEffect)
			{
				for (int i = 0; i < 2; i++)
				{
					line[i].sprite->Draw();
				}
			}
		}
		Sprite::PostDraw();
	}
}

void IntervalScene::Finalize()
{
}

void IntervalScene::Start()
{
	// エフェクト初期化
	startCnt = 0;
	width = 10;

	for (int i = 0; i < 2; i++)
	{
		// 初期位置設定
		line[i].size = { 3000, 10 };
		line[i].position = { -3000, WINDOW_HEIGHT / 2 - 5 };
		line[i].speed = { 70.0f, 0 };
	}

	isEffect = true;
}