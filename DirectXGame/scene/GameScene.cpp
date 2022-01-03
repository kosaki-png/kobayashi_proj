#include "GameScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>
#include <thread>

using namespace DirectX;

GameScene::GameScene(int stage)
	:	stage(stage)
{
}

GameScene::~GameScene()
{
	delete objMng;
	delete player;
	delete[] enemy;

	delete texCol;
	
	delete[] map;
	delete mapAllFrame;
	delete mapAllPoint;
	delete mapAll;
	delete minimap;
	delete miniFrame;

	delete floor;
	delete skydome;

	delete optionSprite;
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptrチェック
	BaseScene::Initialize(dxCommon, input, audio);

	// 汎用的初期化
	{
		// カメラ生成
		//camera = new DebugCamera(WinApp::window_width, WinApp::window_height, input);
		mainCamera = new MainCamera(WinApp::window_width, WinApp::window_height, input);

		// 3Dオブジェクトにカメラをセット
		//Object3d::SetCamera(camera);
		Object3d::SetCamera(mainCamera);

		// デバッグテキスト用テクスチャ読み込み
		if (!Sprite::LoadTexture(texNumber, L"Resources/debugfont.png")) {
			assert(0);
			return;
		}
		// デバッグテキスト初期化
		text = Text::GetInstance();
		text->Initialize(texNumber);

		// ライト生成
		//lightGroup = LightGroup::Create();
		// 3Dオブエクトにライトをセット
		//Object3d::SetLightGroup(lightGroup);

		// デバイスをセット
		Fbx::SetDevice(dxCommon->GetDevice());
		// カメラをセット
		//Fbx::SetCamera(camera);
		Fbx::SetCamera(mainCamera);
		// グラフィックスパイプライン生成
		Fbx::CreateGraphicsPipeline();

		// パーティクルマネージャ生成
		particleMan = ParticleManager::GetInstance();
		//particleMan->SetCamera(camera);
		particleMan->SetCamera(mainCamera);

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
			Sprite::LoadTexture(1, L"Resources/texture/option.png");
			Sprite::LoadTexture(2, L"Resources/texture/miniMap.png");
			Sprite::LoadTexture(3, L"Resources/texture/map_all_frame.png");
			Sprite::LoadTexture(4, L"Resources/texture/map_all_point.png");

			switch (stage)
			{
			case 0:
				Sprite::LoadTexture(5, L"Resources/texture/map_01_ref.png");
				Sprite::LoadTexture(6, L"Resources/texture/map_01_frame.png");
				break;

			case 1:
				Sprite::LoadTexture(5, L"Resources/texture/map_02_ref.png");
				Sprite::LoadTexture(6, L"Resources/texture/map_02_frame.png");
				break;

			default:
				break;
			}
		}

		// スプライト生成
		{
			optionSprite = Sprite::Create(1, { 0,0 });
			miniFrame = Sprite::Create(2, { 1280 - 300, 0 });
			mapAllFrame = Sprite::Create(3, { 0,0 });
			mapAllPoint = Sprite::Create(4, { 0,0 });
			minimap = Sprite::Create(5, { 0,0 });
			mapAll = Sprite::Create(6, { 0,0 });
		}

		// スプライト初期設定
		{
			minimap->SetPosition({ 1280 - 300, -700 });
			minimap->SetSize({ 1000, 1000 });
			minimap->SetPosUV({ 0, 0.7f });
		}
	}

	// FBX初期設定
	{
		// モデルを取得
		modelMng = ModelManager::GetInstance();

		// マップモデルのセット
		for (int i = 0; i < 9; i++)
		{
			map[i] = new Fbx();
			map[i]->Initialize();

			switch (stage)
			{
			case 0:
				map[i]->SetModel(modelMng->GetModel(i + 10));
				map[i]->SetPosition({ -10,0,-1 });

				break;

			case 1:
				map[i]->SetModel(modelMng->GetModel(i + 30));
				map[i]->SetPosition({ -1,0,-1 });
				break;

			default:
				break;
			}
		}

		// 床初期化
		floor = new Fbx();
		floor->Initialize();
		floor->SetModel(modelMng->GetModel(19));
		floor->SetPosition({ 10,3,0 });

		// 空初期化
		skydome = new Fbx();
		skydome->Initialize();
		skydome->SetModel(modelMng->GetModel(20));
		skydome->SetScale({ 2, 2, 2 });
		skydome->SetPosition({ WORLD_WIDTH / 2, 3, WORLD_HEIGHT / 2 });
	}
	
	// 各クラス初期設定
	{
		// 当たり判定用テクスチャのロード
		texCol = new TexCollision(3390, 2775, 1, 1);
		switch (stage)
		{
		case 0:
			texCol->LoadTexture(0, 0, L"Resources/texture/map_01.png");
			//texCol->LoadTexture(0, 0, L"Resources/texture/cleanCol.png");
			break;
		case 1:
			texCol->LoadTexture(0, 0, L"Resources/texture/map_02.png");
			//texCol->LoadTexture(0, 0, L"Resources/texture/cleanCol.png");
			break;
		default:
			break;
		}
		
		// オブジェクトマネージャー生成
		objMng = new ObjectManager();

		// プレイヤー生成
		player = new Player(WinApp::window_width, WinApp::window_height);
		// オブジェクトマネージャーに登録
		objMng->AddObject(player);

		// 敵生成
		for (auto x : enemy)
		{
			x = new Enemy();
			// オブジェクトマネージャーに登録
			objMng->AddObject(x);
		}

		objMng->Initialize(input, texCol);

		player->SetPosition({ 100, 3, 10 });
		
	}

	// カメラの初期設定
	{
	}

	// ゲーム中はマウスカーソルを消す
	ShowCursor(false);

}

void GameScene::Update()
{
	// コントローラの更新
	xinput.Update();

	// パーティクル生成
	//CreateParticles();
	
	// ESCAPEでオプションを開く
	if (input->TriggerKey(DIK_ESCAPE) && !isMap)
	{
		option = !option;
		// マウスカーソルの表示非表示
		ShowCursor(option);
	}

	// オプション中
	if (option)
	{
		// マップ状態は解除
		isMap = false;

		// スペースで指定のシーンへ
		if (input->TriggerKey(DIK_SPACE) || xinput.TriggerButtom(0, xinput_A))
		{
			// セレクトシーンへ
			nextScene = new EndScene();
		}

		// マウスポイント取得
		{
			static POINT p;
			GetCursorPos(&p);
			ScreenToClient(FindWindowA(nullptr, "DirectXGame"), &p);
			mousePos = { (float)p.x, (float)p.y };
		}
	}
	else // ゲーム中
	{
		// 感度の設定
		mainCamera->SetSence(sence);
		player->SetSence(sence);

		// マウスカーソルを画面中心に固定
		SetCursorPos(1920 / 2, 1080 / 2);

		// ミニマップ移動
		XMFLOAT3 playerPos = player->GetPosition();
		playerPos.x /= MAP_WIDTH;
		playerPos.z /= MAP_HEIGHT;
		minimap->SetPosUV({ playerPos.x - 0.15f, playerPos.z -0.15f });

		playerPos = player->GetPosition();
		XMFLOAT2 tmpF2 = { playerPos.x / 4.0f, -playerPos.z / 4.0f };

		// マップ表示
		if (input->TriggerKey(DIK_M))
		{
			isMap = !isMap;
		}
		if (isMap)
		{
			// マップ移動
			mapAllPoint->SetPosition(tmpF2);
			if (input->TriggerKey(DIK_ESCAPE))
			{
				isMap = false;
			}
		}

		// 各種更新
		{
			// マップの更新
			for (int i = 0; i < 9; i++)
			{
				map[i]->Update();
			}

			// 空の更新
			{
				static float angle = 0;
				angle += 0.04f;
				mainCamera->UpdateProjectionMatrix(5000.0f);
				skydome->SetRotation({ 0, angle / 10, 0 });
				skydome->Update();
				mainCamera->UpdateProjectionMatrix(1000.0f);
			}

			// 地面の更新
			floor->Update();

			// オブジェクトマネージャーの更新
			objMng->Update();
			
			// メインカメラの更新
			{
				// プレイヤーの動きをカメラに反映
				XMFLOAT3 cameraMove = { player->GetPosition().x + player->GetMove().x,
										player->GetPosition().y + player->GetMove().y + 2,
										player->GetPosition().z + player->GetMove().z, };
				mainCamera->SetTarget(cameraMove);

				mainCamera->Update();
			}
		}
	}
	
	//lightGroup->Update();
	particleMan->Update();
}

void GameScene::Draw()
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
			objMng->Draw(cmdList);

			// マップモデルの描画
			for (int i = 0; i < 9; i++)
			{
				map[i]->Draw(cmdList, true);
			}
			skydome->Draw(cmdList, true);
			floor->Draw(cmdList, true);
		}
		Object3d::PostDraw();

		// パーティクルの描画
		particleMan->Draw(cmdList);
	}
	
	// 前景スプライト描画
	{
		Sprite::PreDraw(cmdList);
		{
			if (!isMap)
			{
				minimap->Draw();
				miniFrame->Draw();
			}
			else
			{
				mapAllFrame->Draw();
				mapAll->Draw();
				mapAllPoint->Draw();
			}

			// オプション画面
			if (option)
			{
				optionSprite->Draw();
			}

			// デバッグテキストの描画
			text->DrawAll(cmdList);
		}
		Sprite::PostDraw();
	}

	// ImGui描画
	{
		ImGui::Begin("OPTION");
		ImGui::SetWindowSize(ImVec2(100, 100));
		ImGui::SliderFloat("感度", &sence, 0.01f, 5.0f);
		ImGui::End();
	}
}

void GameScene::Finalize()
{
}
