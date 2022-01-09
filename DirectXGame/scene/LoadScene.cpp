#include "LoadScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>

using namespace DirectX;

// モデル管理クラスのインスタンス取得
ModelManager* modelMngLoad = ModelManager::GetInstance();

const int STAGE_COUNT = 3;		// ステージの数

const int LOAD_DEF_MODEL_CNT = 3;		// デフォルトでロードするモデルの数
const int LOAD_STAGE_MODEL_CNT = 10;	// ステージ			〃

// ロードバー割合
float loadRatio[STAGE_COUNT] = { 0, 0, 0 };
int modelCnt = 0;	// 読み込むオブジェクトの数
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
	//ダミーで10秒待つ
	/*auto sleepTime = std::chrono::seconds(10);
	std::this_thread::sleep_for(sleepTime);*/

	// モデルをロードして割合を増やす
	modelMngLoad->Load(0, "player");			AddRatio(stage);	// 0
	modelMngLoad->Load(1, "Enemy");				AddRatio(stage);	// 1
	modelMngLoad->Load(2, "Enemy_circle");		AddRatio(stage);	// 2

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
	switch (stage)
	{
	case 0:
		modelMngLoad->Load(10, "01_87");		AddRatio(stage);	// 10
		modelMngLoad->Load(11, "01_88");		AddRatio(stage);	// 11
		modelMngLoad->Load(12, "01_89");		AddRatio(stage);	// 12
		//modelMng->Load("01_77");	// 13
		modelMngLoad->Load(14, "01_78");		AddRatio(stage);	// 14
		modelMngLoad->Load(15, "01_79");		AddRatio(stage);	// 15
		modelMngLoad->Load(16, "01_67");		AddRatio(stage);	// 16
		modelMngLoad->Load(17, "01_68");		AddRatio(stage);	// 17
		modelMngLoad->Load(18, "01_69");		AddRatio(stage);	// 18
		modelMngLoad->Load(19, "floor");		AddRatio(stage);	// 19
		modelMngLoad->Load(20, "skydome");		AddRatio(stage);	// 20
		break;											 
														 
	case 1:												 
		modelMngLoad->Load(30, "02_51");		AddRatio(stage);	// 30
		modelMngLoad->Load(31, "02_52");		AddRatio(stage);	// 31
		modelMngLoad->Load(32, "02_53");		AddRatio(stage);	// 32
		//modelMng->Load("01_77");	// 33				 
		modelMngLoad->Load(34, "02_42");		AddRatio(stage);	// 34
		modelMngLoad->Load(35, "02_43");		AddRatio(stage);	// 35
		modelMngLoad->Load(36, "02_31");		AddRatio(stage);	// 36
		modelMngLoad->Load(37, "02_32");		AddRatio(stage);	// 37
		modelMngLoad->Load(38, "02_33");		AddRatio(stage);	// 38
		modelMngLoad->Load(39, "floor");		AddRatio(stage);	// 39
		modelMngLoad->Load(40, "skydome");		AddRatio(stage);	// 40
		break;

	case 2:
		modelMngLoad->Load(50, "03_50");		AddRatio(stage);	// 50
		modelMngLoad->Load(51, "03_51");		AddRatio(stage);	// 51
		modelMngLoad->Load(52, "03_52");		AddRatio(stage);	// 52
		//modelMng->Load("01_77");	// 33				 
		modelMngLoad->Load(54, "03_41");		AddRatio(stage);	// 54
		modelMngLoad->Load(55, "03_42");		AddRatio(stage);	// 55
		modelMngLoad->Load(56, "03_30");		AddRatio(stage);	// 56
		modelMngLoad->Load(57, "03_31");		AddRatio(stage);	// 57
		modelMngLoad->Load(58, "03_32");		AddRatio(stage);	// 58
		modelMngLoad->Load(59, "floor");		AddRatio(stage);	// 59
		modelMngLoad->Load(60, "skydome");		AddRatio(stage);	// 60
		break;

	default:
		break;
	}

	SetLoadStage(stage, true);
}

#pragma endregion

void AsyncLoadStage(int stage)
{
	// 予め読み込む数を取得
	modelCnt = 0;	// 一旦初期化
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
}

void LoadScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
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
			Sprite::LoadTexture(1, L"Resources/texture/loading.png");
			Sprite::LoadTexture(2, L"Resources/texture/loaded.png");
			Sprite::LoadTexture(3, L"Resources/texture/load_bar.png");
			Sprite::LoadTexture(4, L"Resources/texture/load_bar_white.png");
		}

		// スプライト生成
		{
			loading = Sprite::Create(1, { 0,0 });
			loaded = Sprite::Create(2, { 0,0 });
			loadBar = Sprite::Create(3, { 0,0 });
			loadBarWhite = Sprite::Create(4, { 243,603 });
		}

		// スプライト初期設定
		{
		}
	}

	// FBXオブジェクト初期設定
	{
		mapObj = new Fbx();
		mapObj->Initialize();
		switch (stage)
		{
		case 0:
			mapObj->SetModel(modelMngLoad->GetModel(13));
			break;
		case 1:
			mapObj->SetModel(modelMngLoad->GetModel(33));
			break;
		case 2:
			mapObj->SetModel(modelMngLoad->GetModel(53));
			break;
		default:
			break;
		}
		mapObj->SetPosition({ -1130 / 2, 0, -925 - 925 / 2 });
	}

	// カメラ初期設定
	{
		//camera->SetMouseFlag(false);
	}

	// 非同期ロード開始
	if (!GetLoadStage(stage))
	{
		th = new std::thread(AsyncLoadStage, stage);
	}
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

	lightGroup->Update();
	particleMan->Update();
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
		Object3d::PreDraw(cmdList);
		{
			// 非同期ロード中
			if (!GetLoadStage(stage))
			{

			}
			else   // ロード終了後
			{

			}

			mapObj->Draw(cmdList, true);
		}
		Object3d::PostDraw();

		// パーティクルの描画
		particleMan->Draw(cmdList);
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

void LoadScene::Finalize()
{
	if (!GetLoadStage)
	{
		th->join();
	}
}
