#include "IntervalScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>

using namespace DirectX;

IntervalScene::IntervalScene()
{
}

IntervalScene::~IntervalScene()
{
	delete line[0].sprite;
	delete line[1].sprite;
}

void IntervalScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptrチェック
	BaseScene::Initialize(dxCommon, input, audio);

	// 汎用的初期化
	{
		// カメラ生成
		camera = new OrbitCamera(WinApp::window_width, WinApp::window_height);

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
			Sprite::LoadTexture(101, L"Resources/texture/white_1000x1000.png");
		}

		// スプライト生成
		{
			for (int i = 0; i < 2; i++)
			{
				// 初期位置設定
				line[i].sprite = Sprite::Create(101, { 0,0 });
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
		//for (int i = 0; i < 4; i++)
		//{
		//	if (trance[i].position.y == 0)
		//	{
		//		trance[i].speed.x = 0.0f;
		//		trance[i].speed.y = 0.0f;
		//	}
		//	// 0.5秒後からスタート
		//	if (startCnt == 30)
		//	{
		//		trance[0].speed.y = WINDOW_HEIGHT / 20.0f;
		//		trance[2].speed.y = -WINDOW_HEIGHT / 20.0f;
		//	}
		//	if (startCnt == 40)
		//	{
		//		trance[1].speed.y = WINDOW_HEIGHT / 20.0f;
		//		trance[3].speed.y = -WINDOW_HEIGHT / 20.0f;
		//	}
		//	//
		//	if (startCnt >= 100 && startCnt < 160)
		//	{
		//		alpha += 0.015f;
		//	}
		//	if (startCnt >= 160 && startCnt < 220)
		//	{
		//		alpha -= 0.015f;
		//	}
		//	// 0.5秒後からスタート
		//	if (startCnt == 230)
		//	{
		//		trance[1].speed.y = -WINDOW_HEIGHT / 20.0f;
		//		trance[3].speed.y = WINDOW_HEIGHT / 20.0f;
		//	}
		//	if (startCnt == 250)
		//	{
		//		trance[0].speed.y = -WINDOW_HEIGHT / 20.0f;
		//		trance[2].speed.y = WINDOW_HEIGHT / 20.0f;
		//	}
		//	// 速度から座標を更新
		//	trance[i].position.x += trance[i].speed.x;
		//	trance[i].position.y += trance[i].speed.y;
		//	// 座標をセット
		//	trance[i].sprite->SetPosition(trance[i].position);
		//	back->SetAlpha(alpha);
		//}
		//// 完全に隠れたタイミング
		//if (startCnt == 160)
		//{
		//	//isCover = true;
		//}

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

	lightGroup->Update();
	particleMan->Update();

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

		// パーティクルの描画
		particleMan->Draw(cmdList);
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

			// デバッグテキストの描画
			text->DrawAll(cmdList);
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