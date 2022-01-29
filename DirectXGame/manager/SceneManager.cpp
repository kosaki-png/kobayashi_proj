#include "SceneManager.h"

SceneManager* SceneManager::instance = nullptr;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	delete scene;
	delete instance;
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
	//scene = new IntervalScene();

	interval = new IntervalScene();

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;

	// 最初のシーンの初期化
	scene->Initialize(this->dxCommon, this->input, this->audio);
	interval->Initialize(this->dxCommon, this->input, this->audio);
}

void SceneManager::Update()
{
	// シーン切り替え
	{
		// シーンクラスで指定した次のシーンを受け取る
		BaseScene* nextScene = scene->GetNextScene();

		if (nextScene)	// nextSceneがnullでないとき
		{
			// エフェクトを起動していないなら起動
			if (!interval->GetIsEffect())
			{
				interval->Start();
			}
			
			if (interval->GetIsCover())
			{
				// 元のシーンを削除
				delete scene;

				// 次に指定したシーンを初期化
				nextScene->Initialize(dxCommon, input, audio);

				// 現在のシーンに適用
				scene = nextScene;
			}
		}
	}

	// シーンの更新
	scene->Update();
	interval->Update();
}

void SceneManager::Draw()
{
	scene->Draw();
	interval->Draw();
}

void SceneManager::Finalize()
{
	scene->Finalize();
	interval->Finalize();
}
