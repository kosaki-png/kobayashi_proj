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
	for (int i = 0; i < 6; i++)
	{
		delete trance[i].trance;
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
		}

		// スプライト生成
		{
			for (int i = 0; i < 6; i++)
			{
				trance[i].trance = Sprite::Create(100, { 0,0 });
				trance[i].position = { i * 320.0f - 160.0f, 720.0f };
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

	// 挙動
	for (int i = 0; i < 6; i++)
	{
		// 移動制限
		if (trance[i].position.y <= -720 || trance[i].position.y >= 0)
		{
			if (startCnt < 130)
			{
				trance[i].speed.x = 0.0f;
				trance[i].speed.y = 0.0f;
			}
		}

		// 一定時間で移動量変更
		// 上から
		if (startCnt == 60 / 6 * i + 30)
		{
			trance[i].speed.x = -320.0f / 30;
			trance[i].speed.y = 20.0f;
		}
		// 左右へ
		if (startCnt == 150)
		{
			for (int i = 0; i < 6; i++)
			{
				if (i < 3)
				{
					trance[i].speed.x = -20;
				}
				else
				{
					trance[i].speed.x = +20;
				}
			}
		}

		// 移動量適用
		trance[i].position.x += trance[i].speed.x;
		trance[i].position.y += trance[i].speed.y;
		trance[i].trance->SetPosition({ trance[i].position });
	}

	if (startCnt == 130)
	{
		isCover = true;
	}

	if (startCnt > 250)
	{
		isEffect = false;
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
			for (int i = 0; i < 6; i++)
			{
				trance[i].trance->Draw();
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
	// 位置初期化
	for (int i = 0; i < 6; i++)
	{
		trance[i].position = { i * 320.0f - 160.0f, -720.0f };
	}
	isEffect = true;
}