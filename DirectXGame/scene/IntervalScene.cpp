#include "IntervalScene.h"

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
	modelMng->Load("floor");	// 10
	modelMng->Load("skydome");	// 11
	//modelMng->Load("player");	// 1
	//modelMng->Load("player");	// 2
	//modelMng->Load("player");	// 3
	//modelMng->Load("player");	// 4
	//modelMng->Load("player");	// 5
	//modelMng->Load("player");	// 6
	//modelMng->Load("player");	// 7
	//modelMng->Load("player");	// 8
	//modelMng->Load("player");	// 9
	//modelMng->Load("player");	// 10
	//modelMng->Load("player");	// 11

	SetLockFlag(true);
}

IntervalScene::IntervalScene()
{
}

IntervalScene::~IntervalScene()
{
}

void IntervalScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// 非同期ロード開始
	if (!isLoaded)
	{
		th = new std::thread(AsyncLoad);
	}
}

void IntervalScene::Update()
{
	// 非同期ロード中
	if (GetLockFlag())
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
}

void IntervalScene::Draw()
{
}

void IntervalScene::Finalize()
{
	if (!isLoaded)
	{
		th->join();
	}
}
