#include "LoadScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>

using namespace DirectX;

// 非同期ロード用
bool isLoadedLoad = false;
std::mutex isLoadedMutexLoad;
// モデル管理クラスのインスタンス取得
ModelManager* modelMngLoad = ModelManager::GetInstance();

// ロードバー割合
float loadRatio = 0;
const int LOAD_MODEL_COUNT = 12;	// 読み込むオブジェクトの数
const float LOAD_RATIO = 1.0f / LOAD_MODEL_COUNT;	// オブジェクトを読み込んだ時に進む割合

// 非同期ロード用
void LoadSetLockFlag(bool _)
{
	std::lock_guard<std::mutex>  lock(isLoadedMutexLoad);
	isLoadedLoad = true;
}

bool LoadGetLockFlag()
{
	std::lock_guard<std::mutex>  lock(isLoadedMutexLoad);
	return isLoadedLoad;
}

// ロードバーを進める
void AddRatio(float rate)
{
	loadRatio += rate;
}

float GetRatio()
{
	return loadRatio;
}

// 非同期ロード関数
void IntervalAsyncLoad()
{
	//ダミーで10秒待つ
	/*auto sleepTime = std::chrono::seconds(10);
	std::this_thread::sleep_for(sleepTime);*/

	// モデルをロードして割合を増やす
	modelMngLoad->Load(0, "player");	AddRatio(LOAD_RATIO);	// 0

	//modelMngLoad->Load(1, "01_87");		AddRatio(LOAD_RATIO);	// 1
	//modelMngLoad->Load(2, "01_88");		AddRatio(LOAD_RATIO);	// 2
	//modelMngLoad->Load(3, "01_89");		AddRatio(LOAD_RATIO);	// 3
	////modelMng->Load("01_77");	// 4
	//modelMngLoad->Load(5, "01_78");		AddRatio(LOAD_RATIO);	// 5
	//modelMngLoad->Load(6, "01_79");		AddRatio(LOAD_RATIO);	// 6
	//modelMngLoad->Load(7, "01_67");		AddRatio(LOAD_RATIO);	// 7
	//modelMngLoad->Load(8, "01_68");		AddRatio(LOAD_RATIO);	// 8
	//modelMngLoad->Load(9, "01_69");		AddRatio(LOAD_RATIO);	// 9

	modelMngLoad->Load(1, "02_51");		AddRatio(LOAD_RATIO);	// 1
	modelMngLoad->Load(2, "02_52");		AddRatio(LOAD_RATIO);	// 2
	modelMngLoad->Load(3, "02_53");		AddRatio(LOAD_RATIO);	// 3
	//modelMng->Load("01_77");	// 4
	modelMngLoad->Load(5, "02_42");		AddRatio(LOAD_RATIO);	// 5
	modelMngLoad->Load(6, "02_43");		AddRatio(LOAD_RATIO);	// 6
	modelMngLoad->Load(7, "02_31");		AddRatio(LOAD_RATIO);	// 7
	modelMngLoad->Load(8, "02_32");		AddRatio(LOAD_RATIO);	// 8
	modelMngLoad->Load(9, "02_33");		AddRatio(LOAD_RATIO);	// 9

	modelMngLoad->Load(10, "floor");	AddRatio(LOAD_RATIO);	// 10
	modelMngLoad->Load(11, "skydome");	AddRatio(LOAD_RATIO);	// 11
	modelMngLoad->Load(12, "Enemy");	AddRatio(LOAD_RATIO);	// 12

	// ロード軽い
	//modelMngLoad->Load(0, "player");	// 0
	//modelMngLoad->Load(1, "player");	// 1
	//modelMngLoad->Load(2, "player");	// 2
	//modelMngLoad->Load(3, "player");	// 3
	////modelMng->Load("01_77");	// 4
	//modelMngLoad->Load(5, "player");	// 5
	//modelMngLoad->Load(6, "player");	// 6
	//modelMngLoad->Load(7, "player");	// 7
	//modelMngLoad->Load(8, "player");	// 8
	//modelMngLoad->Load(9, "player");	// 9
	//modelMngLoad->Load(10, "player");	// 10
	//modelMngLoad->Load(11, "player");	// 11
	//modelMngLoad->Load(12, "player");	// 12

	LoadSetLockFlag(true);
}

LoadScene::LoadScene()
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
		kogakuin = new Fbx();
		kogakuin->Initialize();
		kogakuin->SetModel(modelMngLoad->GetModel(4));
		kogakuin->SetPosition({ -1130 / 2, 0, -925 - 925 / 2 });
	}

	// カメラ初期設定
	{
		//camera->SetMouseFlag(false);
	}

	// 非同期ロード開始
	if (!isLoadedLoad)
	{
		th = new std::thread(IntervalAsyncLoad);
	}
}

void LoadScene::Update()
{
	// 非同期ロード中
	if (!LoadGetLockFlag())
	{

	}
	else   // ロード終了後
	{
		// SPACEで次のシーン
		if (input->TriggerKey(DIK_SPACE))
		{
			nextScene = new GameScene();
		}
	}

	// ロードバー加算
	float bar = GetRatio() * 800.0f;
	loadBarWhite->SetPosUV({ -GetRatio() + 1.0f, 0 });

	// FBX更新
	{
		kogakuin->Update();
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
			if (!LoadGetLockFlag())
			{

			}
			else   // ロード終了後
			{

			}

			kogakuin->Draw(cmdList, true);
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
			if (!LoadGetLockFlag())
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
	if (!isLoadedLoad)
	{
		th->join();
	}
}
