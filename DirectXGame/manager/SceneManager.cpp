#include "SceneManager.h"

SceneManager* SceneManager::instance = nullptr;


SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	delete scene;
}

SceneManager* SceneManager::GetInstance()
{
	if (!instance)
	{
		instance = new SceneManager();
	}
	return instance;
}

void SceneManager::Destroy()
{
	SceneManager::~SceneManager();
}

void SceneManager::Start(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// 最初のシーン
	scene = new TitleScene();
	//scene = new SelectScene();
	//scene = new GameScene();
	//scene = new EndScene();

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;

	// 最初のシーンの初期化
	scene->Initialize(this->dxCommon, this->input, this->audio);
}

void SceneManager::Update()
{
	// シーン切り替え
	{
		// シーンクラスで指定した次のシーンを受け取る
		BaseScene* nextScene = scene->GetNextScene();

		if (nextScene)	// nextSceneがnullでないとき
		{
			//interval->Initialize(dxCommon, input, audio);

			// 元のシーンを削除
			delete scene;

			// 次に指定したシーンを初期化
			nextScene->Initialize(dxCommon, input, audio);

			// 現在のシーンに適用
			scene = nextScene;
		}
	}

	// シーンの更新
	scene->Update();
}

void SceneManager::Draw()
{
	scene->Draw();
}

void SceneManager::Finalize()
{
	scene->Finalize();
}
