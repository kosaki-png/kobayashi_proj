#include "LoadScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>

using namespace DirectX;
using namespace SpriteData;

// モデル管理クラスのインスタンス取得
ModelManager* modelMngLoad = ModelManager::GetInstance();

const int STAGE_COUNT = 4;		// ステージの数

const int LOAD_DEF_MODEL_CNT = 7;		// デフォルトでロードするモデルの数
const int LOAD_STAGE_MODEL_CNT = 11;	// ステージ			〃

// ロードバー割合
float loadRatio[STAGE_COUNT] = { 0, 0, 0 };
float ratioPiece = 0;	// オブジェクトを読み込んだ時に進む割合

// ロードバーを進める
void AddRatio(int stage)
{
	loadRatio[stage] += ratioPiece;
}
float GetRatio(int stage)
{
	return loadRatio[stage];
}

#pragma region デフォルトロード

#pragma region トリガー系

bool loadDefault = false;
std::mutex mutexDefault;

void SetLoadDefault(bool flag)
{
	std::lock_guard<std::mutex>  lock(mutexDefault);
	loadDefault = flag;
}
bool GetLoadDefault()
{
	std::lock_guard<std::mutex>  lock(mutexDefault);
	return loadDefault;
}

#pragma endregion

void LoadDefault(int stage)
{
	// 指定したステージ情報の取得
	std::vector<std::string> modelName = StageDataStorage::GetInstance()->GetDefoultName();

	// ステージ情報からモデルをロード
	for (int i = 0; i < modelName.size(); i++)
	{
		modelMngLoad->Load(i, modelName[i]);
		AddRatio(stage);
	}

	//ダミーで10秒待つ
	/*auto sleepTime = std::chrono::seconds(10);
	std::this_thread::sleep_for(sleepTime);*/

	SetLoadDefault(true);
}

#pragma endregion

#pragma region ステージロード

#pragma region トリガー系

bool loadStage[STAGE_COUNT] = {};
std::mutex mutexStage[STAGE_COUNT];

// ロードトリガー系
void SetLoadStage(int stage, bool flag)
{
	std::lock_guard<std::mutex>  lock(mutexStage[stage]);
	loadStage[stage] = flag;
}
bool GetLoadStage(int stage)
{
	std::lock_guard<std::mutex>  lock(mutexStage[stage]);
	return loadStage[stage];
}

#pragma endregion

// ステージのロード
void LoadStage(int stage)
{
	// 指定したステージ情報の取得
	StageDataStorage::StageData stageData = StageDataStorage::GetInstance()->GetStageData(stage);

	// ステージ情報からモデルをロード
	for (int i = 0; i < stageData.modelName.size(); i++)
	{
		modelMngLoad->Load(stageData.firstNum + i, stageData.modelName[i]);
		AddRatio(stage);
	}

	SetLoadStage(stage, true);
}

#pragma endregion

void AsyncLoadStage(int stage)
{
	// 予め読み込む数を取得
	int modelCnt = 0;
	if (!GetLoadDefault())
	{
		modelCnt += LOAD_DEF_MODEL_CNT;
	}
	if (!GetLoadStage(stage))
	{
		modelCnt += LOAD_STAGE_MODEL_CNT;

		// バーを進める値設定
		ratioPiece = 1.0f / modelCnt;
	}

	// ロードしてないならする
	if (!GetLoadDefault())
	{
		LoadDefault(stage);
	}
	if (!GetLoadStage(stage))
	{
		LoadStage(stage);
	}
}

LoadScene::LoadScene(int stage)
	:	stage(stage)
{
}

LoadScene::~LoadScene()
{
	delete mapObj;
	delete loading;
	delete loaded;
	delete loadBar;
	delete loadBarWhite;
}

void LoadScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
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
			if (!SpriteLoader::GetLoadFlag())
			{
				SpriteLoader::LoadLoadSprite();
			}
		}

		// スプライト生成
		{
			loading = Sprite::Create(LOADING, { 0,0 });
			loaded = Sprite::Create(LOADED, { 0,0 });
			loadBar = Sprite::Create(LOADFLAME, { 0,0 });
			loadBarWhite = Sprite::Create(LOADBAR, { 243,603 });
		}

		// スプライト初期設定
		{
			// ロードバーなどの色をセット
			XMFLOAT4 color = { stageData->GetStageData(stage).color.x,
							   stageData->GetStageData(stage).color.y,
							   stageData->GetStageData(stage).color.z, 1 };
			loading->SetColor(color);
			loaded->SetColor(color);
			loadBar->SetColor(color);
		}
	}

	// FBXオブジェクト初期設定
	{
		mapObj = new Fbx();
		mapObj->Initialize();
		// マップモデルセット
		mapObj->SetModel(modelMngLoad->GetModel(stage * 20 + 23));
		mapObj->SetPosition({ -1130 / 2, 0, -925 - 925 / 2 });
		mapObj->SetFogColor(stageData->GetStageData(stage).fogColor);
	}

	// 非同期ロード開始
	if (!GetLoadStage(stage))
	{
		th = new std::thread(AsyncLoadStage, stage);
	}

	isGodray = true;
}

void LoadScene::Update()
{
	// 非同期ロード中
	if (!GetLoadStage(stage))
	{

	}
	else   // ロード終了後
	{
		// SPACEで次のシーン
		if (input->TriggerKey(DIK_SPACE))
		{
			nextScene = new GameScene(stage);
		}
	}

	// ロードバー加算
	float bar = GetRatio(stage) * 800.0f;
	loadBarWhite->SetPosUV({ -GetRatio(stage) + 1.0f, 0 });

	// FBX更新
	{
		mapObj->Update();
	}

	// カメラ更新
	{
		camera->Update();
	}
}

void LoadScene::Draw()
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
		// マップ描画
		mapObj->Draw(cmdList);
	}

	// 前景スプライト描画
	{
		Sprite::PreDraw(cmdList);
		{
			// ロードバー
			loadBarWhite->Draw();
			loadBar->Draw();
			// 非同期ロード中
			if (!GetLoadStage(stage))
			{
				loading->Draw();
			}
			else   // ロード終了後
			{
				loaded->Draw();
			}
		}
		Sprite::PostDraw();
	}
}

void LoadScene::Finalize()
{
	if (!GetLoadStage(stage))
	{
		th->join();
	}
}
