#include "GameScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>
#include <thread>

using namespace DirectX;
using namespace SpriteData;

GameScene::GameScene(int stage)
	:	stage(stage)
{
}

GameScene::~GameScene()
{
	delete nextScene;
	delete camera;
	delete player;

	for (auto x : crystal)
	{
		delete x;
	}
	for (auto x : gush)
	{
		delete x;
	}
	delete objMng;
	/*for (auto x : enemy)
	{
		delete x;
	}*/

	delete texCol;
	
	// マップ系
	for (auto x : map)
	{
		delete x;
	}
	delete minimap;
	delete miniFrame;
	delete mapCursor;
	delete mapAllFrame;
	delete mapAllPoint;
	delete mapAll;

	delete floor;
	delete skydome;

	delete optionSprite;
	delete cursorSprite;
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptrチェック
	BaseScene::Initialize(dxCommon, input, audio);

	// 汎用的初期化
	{
		// カメラ生成
		camera = new MainCamera(WinApp::window_width, WinApp::window_height, input);

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
			if (!SpriteLoader::GetGameFlag())
			{
				SpriteLoader::LoadGameSprite();
			}
		}

		// スプライト生成
		{
			optionSprite = Sprite::Create(OPTION, { 0,0 });
			miniFrame = Sprite::Create(MAP_MINI, { 1280 - 300, 0 });
			mapAllFrame = Sprite::Create(MAP_FLAME, { 0,0 });
			mapAllPoint = Sprite::Create(MAP_POINT, { 0,0 });
			mapCursor = Sprite::Create(MAP_CURSOR, { 1280 - 150, 150});
			minimap = Sprite::Create(stage + MAP01_REF, { 0,0 });
			mapAll = Sprite::Create(stage + MAP01_FLAME, { 0,0 });
		}

		// スプライト初期設定
		{
			minimap->SetPosition({ 1280 - 300, -700 });
			minimap->SetSize({ 1000, 1000 });
			minimap->SetPosUV({ 0, 0.7f });

			mapCursor->SetAnchorPoint({ 0.5f, 0.5f });
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

			// マップモデルセット
			map[i]->SetModel(modelMng->GetModel(i + stageData->GetStageData(stage).firstNum));
			map[i]->SetPosition({ stageData->GetStageData(stage).gap });

			// フォグの色設定
			map[i]->SetFogColor(stageData->GetStageData(stage).fogColor);
		}

		// 床初期化
		floor = new Fbx();
		floor->Initialize({ 0, -1, 0 });

		// 空初期化
		skydome = new Fbx();
		skydome->Initialize({ 0, -1, 0 });
		skydome->SetFog(false);

		// モデルセット
		floor->SetModel(modelMng->GetModel(stageData->GetStageData(stage).firstNum + 9));
		skydome->SetModel(modelMng->GetModel(stageData->GetStageData(stage).firstNum + 10));

		// 床初期値
		floor->SetPosition({ 10,0,0 });

		// 空初期値
		skydome->SetScale({ 2, 2, 2 });
		skydome->SetPosition({ WORLD_WIDTH / 2, 0, WORLD_HEIGHT / 2 });
	}

	// 当たり判定用テクスチャのロード
	{
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
		case 2:
			texCol->LoadTexture(0, 0, L"Resources/texture/map_03.png");
			//texCol->LoadTexture(0, 0, L"Resources/texture/cleanCol.png");
			break;
		case 3:
			texCol->LoadTexture(0, 0, L"Resources/texture/map_04.png");
			//texCol->LoadTexture(0, 0, L"Resources/texture/cleanCol.png");
			break;
		default:
			break;
		}
	}

	// エレメント初期化
	{
		// オブジェクトマネージャー生成
		objMng = new ObjectManager();

		// プレイヤー生成
		player = new Player(WinApp::window_width, WinApp::window_height);
		// オブジェクトマネージャーに登録
		objMng->AddObject(player);

		// 敵生成
		//for (int i = 0; i < ENEMY_COUNT; i++)
		//{
		//	enemy[i] = new Enemy();
		//	// オブジェクトマネージャーに登録
		//	objMng->AddObject(enemy[i]);
		//}

		// クリスタル生成
		for (int i = 0; i < CRYSTAL_COUNT; i++)
		{
			crystal[i] = new Crystal();
			// オブジェクトマネージャーに登録
			objMng->AddObject(crystal[i]);
		}

		// オブジェクト初期化
		objMng->Initialize(input, texCol);
	}
	
	// その他各クラス初期設定
	{	
		// パーティクル生成
		for (int i = 0; i < GUSH_COUNT; i++)
		{
			gush[i] = new Gush();
			gush[i]->Initialize();
		}
	}

	// クリスタルの座標を保存
	for (int i = 0; i < CRYSTAL_COUNT; i++)
	{
		crystalPos[i] = crystal[i]->GetPosition();
	}

	// カメラの初期設定
	{
	}

	// ゲーム中はマウスカーソルを消す
	ShowCursor(false);

	isGodray = false;
}

void GameScene::Update()
{
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
		if (input->TriggerKey(DIK_SPACE))
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
		//// 感度の設定
		//camera->SetSence(sence);
		//player->SetSence(sence);

		// マウスカーソルを画面中心に固定
		SetCursorPos(1920 / 2, 1080 / 2);

		// ミニマップ移動
		XMFLOAT3 playerPos = player->GetPosition();
		minimap->SetPosUV({ playerPos.x / MAP_WIDTH - 0.15f, playerPos.z / MAP_HEIGHT -0.15f });

		// マップ表示
		if (input->TriggerKey(DIK_M))
		{
			isMap = !isMap;
		}
		if (isMap)
		{
			// マップ移動
			mapAllPoint->SetPosition({ playerPos.x / 4.0f, -playerPos.z / 4.0f });
			if (input->TriggerKey(DIK_ESCAPE))
			{
				isMap = false;
			}
		}

		// プレイヤーと敵の判定
		{
			player->SetDanger(false);

			//for (int i = 0; i < ENEMY_COUNT; i++)
			//{
			//	// 敵と自機の距離
			//	XMFLOAT3 lengthPE = { enemy[i]->GetPosition().x - playerPos.x, 0, enemy[i]->GetPosition().z - playerPos.z };
			//	enemy[i]->SetTrack(false);
			//	// 一旦大まかに四角の判定
			//	if (abs(lengthPE.x) < 75 && abs(lengthPE.z) < 75)
			//	{
			//		double tmpLength = sqrt(pow(lengthPE.x, 2) + pow(lengthPE.z, 2));
			//		// 円状の判定
			//		if (tmpLength < 75)
			//		{
			//			player->SetDanger(true);
			//			// プレイヤーが走っていたら追いかけ始める
			//			if (input->TriggerKey(DIK_LSHIFT))
			//			{
			//				enemy[i]->SetTrack(true);
			//			}
			//		}
			//	}
			//}
		}

		// クリスタル判定
		{
			float dis = 0;
			XMFLOAT3 tmpPos = { 0,0,0 };
			for (int i = 0; i < CRYSTAL_COUNT; i++)
			{
				// クリスタルとの当たり判定
				if (abs(crystalPos[i].x + 0.5f - playerPos.x) <= 1.0f && abs(crystalPos[i].z + 0.5f - playerPos.z) <= 1.0f)
				{
					crystalPos[i] = { -4000,0,0 };
					crystal[i]->SetIsDead(true);
					clearCnt++;
				}

				// 一番近くのクリスタル判定
				float tmpDis = (float)sqrt(pow(crystalPos[i].x - playerPos.x, 2) + pow(crystalPos[i].z - playerPos.z, 2));
				if (dis > tmpDis || dis == 0)
				{
					dis = tmpDis;
					tmpPos = crystalPos[i];
				}
			}

			// 自機とクリスタルの位置から角度を計算
			player->SetCrystalRad(atan2(tmpPos.x - playerPos.x, tmpPos.z - playerPos.z));
		}

		// ゲームクリア
		if (clearCnt == CRYSTAL_COUNT)
		{
			nextScene = new EndScene();
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
				camera->UpdateProjectionMatrix(5000.0f);
				skydome->SetRotation({ 0, angle / 10, 0 });
				skydome->Update();
				camera->UpdateProjectionMatrix(500.0f);
			}

			// 地面の更新
			floor->Update();

			// パーティクルの更新
			for (auto x : gush)
			{
				x->SetPlayerPos(playerPos);
				x->Update();
			}

			// オブジェクトマネージャーの更新
			objMng->Update(player->GetPosition(), 500);
			
			// メインカメラの更新
			{
				// プレイヤーの動きをカメラに反映
				XMFLOAT3 cameraMove = { player->GetPosition().x + player->GetMove().x,
										player->GetPosition().y + player->GetMove().y + 2,
										player->GetPosition().z + player->GetMove().z, };
				camera->SetTarget(cameraMove);

				camera->Update();
			}
		}
	}
	
	mapCursor->SetRotation(player->GetRotation().y);
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
		objMng->Draw(cmdList, player->GetPosition(), 500);

		// マップモデルの描画
		for (auto x : map)
		{
			x->Draw(cmdList);
		}
		skydome->Draw(cmdList);
		floor->Draw(cmdList);
		for (auto x : gush)
		{
			x->Draw(cmdList);
		}	
	}
	
	// 前景スプライト描画
	{
		Sprite::PreDraw(cmdList);
		{
			objMng->SpriteDraw();

			if (!isMap)
			{
				minimap->Draw();
				miniFrame->Draw();
				mapCursor->Draw();
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

void GameScene::Finalize()
{
	delete nextScene;
	delete camera;
	delete player;

	for (auto x : crystal)
	{
		delete x;
	}
	for (auto x : gush)
	{
		delete x;
	}
	delete objMng;
	/*for (auto x : enemy)
	{
		delete x;
	}*/

	delete texCol;

	// マップ系
	for (auto x : map)
	{
		delete x;
	}
	delete minimap;
	delete miniFrame;
	delete mapCursor;
	delete mapAllFrame;
	delete mapAllPoint;
	delete mapAll;

	delete floor;
	delete skydome;

	delete optionSprite;
	delete cursorSprite;
}