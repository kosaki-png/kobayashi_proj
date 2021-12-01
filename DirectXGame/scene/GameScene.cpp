#include "GameScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>
#include <thread>

using namespace DirectX;

// 非同期ロード用
bool isLoaded = false;
std::mutex isLoadedMutex;
// モデル管理クラスのインスタンス取得
ModelManager* modelMng = ModelManager::GetInstance();

// 非同期ロード用
void SetLockFlag(bool _)
{
	std::lock_guard<std::mutex>  lock(isLoadedMutex);
	isLoaded = true;
}

bool GetLockFlag()
{
	std::lock_guard<std::mutex>  lock(isLoadedMutex);
	return isLoaded;
}

// 非同期ロード関数
void AsyncLoad()
{
	//ダミーで10秒待つ
	/*auto sleepTime = std::chrono::seconds(10);
	std::this_thread::sleep_for(sleepTime);*/

	modelMng->Load("player");	// 0
	modelMng->Load("01_87");	// 1
	modelMng->Load("01_88");	// 2
	modelMng->Load("01_89");	// 3
	modelMng->Load("01_77");	// 4
	modelMng->Load("01_78");	// 5
	modelMng->Load("01_79");	// 6
	modelMng->Load("01_67");	// 7
	modelMng->Load("01_68");	// 8
	modelMng->Load("01_69");	// 9
	modelMng->Load("floor_tmp");	// 10

	SetLockFlag(true);
}

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	delete load;
	delete player;
	delete objMng;
	delete texCol;
	delete[] map;
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
		lightGroup = LightGroup::Create();
		// 3Dオブエクトにライトをセット
		Object3d::SetLightGroup(lightGroup);

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
			Sprite::LoadTexture(1, L"Resources/texture/load.png");
			Sprite::LoadTexture(2, L"Resources/texture/option.png");
			Sprite::LoadTexture(3, L"Resources/texture/mouseCursor.png");
			Sprite::LoadTexture(4, L"Resources/texture/loadCircle.png");
		}

		// スプライト生成
		{
			load = Sprite::Create(1, { 0,0 });
			optionSprite = Sprite::Create(2, { 0,0 });
			cursorSprite = Sprite::Create(3, { 0,0 });
			loadcircle = Sprite::Create(4, { 1280 / 2, 720 / 2 });
		}

		// スプライト初期設定
		{
			loadcircle->SetSize({ 300, 300 });
			loadcircle->SetAnchorPoint({ 0.5f, 0.5f });
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
		// モデル読み込み
		{
			// 非同期ロード開始
			if (!isLoaded)
			{
				th = new std::thread(AsyncLoad);

				/*bool* lFbxMode = &fbxMode;
				ModelManager* lModelMng = &modelMng;
				th = new std::thread(
					[modelMng]()
					{

					}
				);*/
			}
		}

		// 3Dオブジェクト生成
		{
		}

		// 3Dオブジェクト初期設定
		{
		}
	}

	// カメラの初期設定
	{
	}

	// ロード画面配置
	load->SetAnchorPoint({ 0.5f, 0.5f });
	load->SetPosition({ 1280 / 2, 720 / 2 });

	// ゲーム中はマウスカーソルを消す
	ShowCursor(false);

	// フェードの初期化
	//fade->Initialize();
	// フェード開始
	//fade->StartEffect()

	// 各クラス生成
	{
		objMng = new ObjectManager();
		player = new Player(WinApp::window_width, WinApp::window_height);
	}
	
	// 各クラス初期設定
	{
		// オブジェクトマネージャーに登録
		objMng->AddObject(player);
	}

	// 当たり判定用テクスチャのロード
	texCol = new TexCollision(3390, 2775, 1, 1);
	texCol->LoadTexture(0, 0, L"Resources/texture/map_01.png");
	/*texCol->LoadTexture(0, 0, L"Resources/texture/Red_1130x925.png");
	texCol->LoadTexture(0, 1, L"Resources/texture/Red_1130x925.png");
	texCol->LoadTexture(0, 2, L"Resources/texture/Red_1130x925.png");
	texCol->LoadTexture(1, 0, L"Resources/texture/Red_1130x925.png");
	texCol->LoadTexture(1, 1, L"Resources/texture/Red_1130x925.png");
	texCol->LoadTexture(1, 2, L"Resources/texture/Red_1130x925.png");
	texCol->LoadTexture(2, 0, L"Resources/texture/Red_1130x925.png");
	texCol->LoadTexture(2, 1, L"Resources/texture/Red_1130x925.png");
	texCol->LoadTexture(2, 2, L"Resources/texture/Red_1130x925.png");*/
	//texCol->LoadTexture(0, 1, L"Resources/texture/01_33.png");
}

void GameScene::Update()
{
	// コントローラの更新
	xinput.Update();

	// 非同期ロードトリガー
	if (GetLockFlag() && !isInit)
	{
		// フェード開始
		//fade->StartEffect();
		objMng->Initialize(input);
		player->SetPosition({ 100, 5, 10 });

		// マップモデルのセット
		for (int i = 0; i < 9; i++)
		{
			map[i] = new Fbx();
			map[i]->Initialize();
			map[i]->SetModel(modelMng->GetModel(i + 1));
			map[i]->SetPosition({ -10,0,-1 });
		}
		worldBox = new Fbx();
		worldBox->Initialize();
		worldBox->SetModel(modelMng->GetModel(10));
		worldBox->SetPosition({ 0, 3, 0 });

		isInit = true;
	}

	// 非同期ロード中
	if (!GetLockFlag())
	{
		static float a;
		a = loadcircle->GetRotation();
		a += 5;
		loadcircle->SetRotation(a);
	}
	else
	{
		// スペースで指定のシーンへ
		if (input->TriggerKey(DIK_SPACE) || xinput.TriggerButtom(0, xinput_A))
		{
			//fade->InStart(false);
			//nextSceneFlag = true;
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

		// パーティクル生成
		//CreateParticles();

		// オプション設定
		{
			// ESCAPEでオプションを開く
			if (input->TriggerKey(DIK_ESCAPE))
			{
				option = !option;
				// マウスカーソルの表示非表示
				ShowCursor(option);
			}

			// オプション中か
			if (!option)
			{
				// マウスカーソルを画面中心に固定
				//static POINT pos = { 1920 / 2, 1080 / 2 };
				//ScreenToClient(FindWindowA(nullptr, "DirectXGame"), &pos);
				SetCursorPos(1920 / 2, 1080 / 2);

				// カメラの移動用更新
				//camera->Update();

				// 各種更新
				{
					for (int i = 0; i < 9; i++)
					{
						map[i]->Update();
					}
					worldBox->Update();

					//map[0][0]->SetPosition({ 0,0,0 });
					//map[0][1]->SetPosition({ 1130, 0, 0 });

					objMng->Update();

					// 戻す移動量取得
					XMFLOAT3 move = texCol->Hit2Color(ArgColor::Red, player->GetPosition(), player->GetMove());
					player->Setmove(move);
					mainCamera->SetTarget({ player->GetPosition().x + move.x,
											player->GetPosition().y + move.y,
											player->GetPosition().z + move.z });
					
					mainCamera->Update();
				}

				/*XMFLOAT4 tmp1 = texCol->GetPixelColor({ 1149, 0, 899 });
				XMFLOAT4 tmp2 = texCol->GetPixelColor(player->GetPosition());
				bool temp3 = texCol->GetHitFlag(ArgColor::Red, { 0,0,0 });*/
			}
			else
			{
			}
		}
	}

	lightGroup->Update();
	particleMan->Update();

	// 3Dオブジェクト更新
	{
	}

	// フェードの更新
	fade->Update();

	// ロードのトリガー用
	preload = GetLockFlag();
}

void GameScene::Draw()
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

		// スプライト描画後処理
		Sprite::PostDraw();
		// 深度バッファクリア
		dxCommon->ClearDepthBuffer();
	}

	// 3D描画
	{
		// 3Dオブジェクトの描画
		Object3d::PreDraw(cmdList);

		/// <summary>
		/// ここに3Dオブジェクトの描画処理を追加
		/// </summary>

		// 非同期ロード終了後
		if (GetLockFlag() == true)
		{
			objMng->Draw(cmdList);

			// マップモデルの
			for (int i = 0; i < 9; i++)
			{
				map[i]->Draw(cmdList, true);
			}
			worldBox->Draw(cmdList, true);
			/*mainCamera->UpdateProjectionMatrix(4000.0f);
			worldBox->Draw(cmdList, true);
			mainCamera->UpdateProjectionMatrix(1000.0f);*/
		}

		Object3d::PostDraw();

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

		// 非同期ロード中
		if (!GetLockFlag())
		{
			load->Draw();
			loadcircle->Draw();
		}

		// オプション画面
		if (option)
		{
			optionSprite->Draw();
		}

		// フェードの描画
		fade->Draw();

		// デバッグテキストの描画
		text->DrawAll(cmdList);

		// スプライト描画後処理
		Sprite::PostDraw();
	}
}

void GameScene::Finalize()
{
	if (!isLoaded)
	{
		th->join();
	}
}