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
	delete back;
	for (int i = 0; i < 4; i++)
	{
		delete trance[i].sprite;
	}
}

void IntervalScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptrチェック
	BaseScene::Initialize(dxCommon, input, audio);

	// 汎用的初期化
	{
		// カメラ生成
		camera = new OrbitCamera(WinApp::window_width, WinApp::window_height);

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
			Sprite::LoadTexture(100, L"Resources/texture/trance.png");
			Sprite::LoadTexture(101, L"Resources/texture/interval_back.png");
			Sprite::LoadTexture(102, L"Resources/texture/interval_up.png");
			Sprite::LoadTexture(103, L"Resources/texture/interval_left.png");
			Sprite::LoadTexture(104, L"Resources/texture/interval_down.png");
			Sprite::LoadTexture(105, L"Resources/texture/interval_right.png");
		}

		// スプライト生成
		{
			back = Sprite::Create(101, { 0,0 });
			back->SetAlpha(0);

			for (int i = 0; i < 4; i++)
			{
				trance[i].sprite = Sprite::Create(102 + i, { 0,0 });
				// 初期位置設定
				if (i < 2)
				{
					trance[i].position = { 10000, -WINDOW_HEIGHT };
				}
				else
				{
					trance[i].position = { 10000,  WINDOW_HEIGHT };
				}

				trance[i].sprite->SetPosition(trance[i].position);
			}
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
		for (int i = 0; i < 4; i++)
		{
			if (trance[i].position.y == 0)
			{
				trance[i].speed.x = 0.0f;
				trance[i].speed.y = 0.0f;
			}

			// 0.5秒後からスタート
			if (startCnt == 30)
			{
				trance[0].speed.y = WINDOW_HEIGHT / 20.0f;
				trance[2].speed.y = -WINDOW_HEIGHT / 20.0f;
			}
			if (startCnt == 40)
			{
				trance[1].speed.y = WINDOW_HEIGHT / 20.0f;
				trance[3].speed.y = -WINDOW_HEIGHT / 20.0f;
			}

			//
			if (startCnt >= 100 && startCnt < 160)
			{
				alpha += 0.015f;
			}

			if (startCnt >= 160 && startCnt < 220)
			{
				alpha -= 0.015f;
			}

			// 0.5秒後からスタート
			if (startCnt == 230)
			{
				trance[1].speed.y = -WINDOW_HEIGHT / 20.0f;
				trance[3].speed.y = WINDOW_HEIGHT / 20.0f;
			}
			if (startCnt == 250)
			{
				trance[0].speed.y = -WINDOW_HEIGHT / 20.0f;
				trance[2].speed.y = WINDOW_HEIGHT / 20.0f;
			}

			// 速度から座標を更新
			trance[i].position.x += trance[i].speed.x;
			trance[i].position.y += trance[i].speed.y;

			// 座標をセット
			trance[i].sprite->SetPosition(trance[i].position);

			back->SetAlpha(alpha);
		}

		// 完全に隠れたタイミング
		if (startCnt == 160)
		{
			isCover = true;
		}

		// エフェクト終了
		if (startCnt > 270)
		{
			isEffect = false;
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
			if (isEffect)
			{
				back->Draw();
				for (int i = 3; i >= 0; i--)
				{
					trance[i].sprite->Draw();
				}
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
}

void IntervalScene::Start()
{
	// エフェクト初期化
	startCnt = 0;
	alpha = 0.0f;

	for (int i = 0; i < 4; i++)
	{
		// 初期位置設定
		if (i < 2)
		{
			trance[i].position = { 0, -WINDOW_HEIGHT };
		}
		else
		{
			trance[i].position = { 0,  WINDOW_HEIGHT };
		}
	}

	isEffect = true;
}