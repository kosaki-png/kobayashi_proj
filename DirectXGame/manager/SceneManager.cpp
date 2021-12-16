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
	// �ŏ��̃V�[��
	scene = new TitleScene();
	//scene = new SelectScene();
	//scene = new GameScene();
	//scene = new EndScene();

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;

	// �ŏ��̃V�[���̏�����
	scene->Initialize(this->dxCommon, this->input, this->audio);
}

void SceneManager::Update()
{
	// �V�[���؂�ւ�
	{
		// �V�[���N���X�Ŏw�肵�����̃V�[�����󂯎��
		BaseScene* nextScene = scene->GetNextScene();

		if (nextScene)	// nextScene��null�łȂ��Ƃ�
		{
			//interval->Initialize(dxCommon, input, audio);

			// ���̃V�[�����폜
			delete scene;

			// ���Ɏw�肵���V�[����������
			nextScene->Initialize(dxCommon, input, audio);

			// ���݂̃V�[���ɓK�p
			scene = nextScene;
		}
	}

	// �V�[���̍X�V
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
