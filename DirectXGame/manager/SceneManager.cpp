#include "SceneManager.h"

SceneManager* SceneManager::instance = nullptr;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
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
	delete interval;
	delete scene;
	delete postEffect;
	delete instance;
}

void SceneManager::Start(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// 最初のシーン
	scene = new TitleScene();
	//scene = new SelectScene();
	//scene = new GameScene();
    //scene = new EndScene(1);
	//scene = new IntervalScene();

	interval = new IntervalScene();

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;

	postEffect = new PostEffect();
	postEffect->Initialize();

	// 最初のシーンの初期化
	scene->Initialize(this->dxCommon, this->input, this->audio);
	interval->Initialize(this->dxCommon, this->input, this->audio);

	postEffect->SetGodray(scene->GetGodrayFlag());
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
				interval->SetTrans(scene->GetTrans());
				interval->Start();
			}
			
			if (interval->GetIsCover())
			{
				// 元のシーンを削除
				delete scene;

				// 次に指定したシーンを初期化
				nextScene->Initialize(dxCommon, input, audio);

				postEffect->SetGodray(nextScene->GetGodrayFlag());

				// 現在のシーンに適用
				scene = nextScene;
			}
		}
	}

	// シーンの更新
	scene->Update();
	interval->Update();

	// ゴッドレイの更新
	postEffect->SetCameraRot(scene->GetCameraRot());
	postEffect->SetIsGame(scene->GetIsGame());
}

void SceneManager::Draw()
{
	postEffect->PreDrawScene(dxCommon->GetCommandList());
	scene->Draw();
	postEffect->PostDrawScene(dxCommon->GetCommandList());
}

void SceneManager::PostEffectDraw()
{
	// ポストエフェクトの描画
	postEffect->Draw(dxCommon->GetCommandList());
	scene->FrontDraw();
	interval->Draw();
}

void SceneManager::Finalize()
{
	scene->Finalize();
	interval->Finalize();
}
