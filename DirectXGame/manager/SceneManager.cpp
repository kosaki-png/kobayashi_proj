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
	//scene = new IntervalScene();

	interval = new IntervalScene();

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;

	// �ŏ��̃V�[���̏�����
	scene->Initialize(this->dxCommon, this->input, this->audio);
	interval->Initialize(this->dxCommon, this->input, this->audio);
}

void SceneManager::Update()
{
	// �V�[���؂�ւ�
	{
		// �V�[���N���X�Ŏw�肵�����̃V�[�����󂯎��
		BaseScene* nextScene = scene->GetNextScene();

		if (nextScene)	// nextScene��null�łȂ��Ƃ�
		{
			// �G�t�F�N�g���N�����Ă��Ȃ��Ȃ�N��
			if (!interval->GetIsEffect())
			{
				interval->Start();
			}
			
			if (interval->GetIsCover())
			{
				// ���̃V�[�����폜
				delete scene;

				// ���Ɏw�肵���V�[����������
				nextScene->Initialize(dxCommon, input, audio);

				// ���݂̃V�[���ɓK�p
				scene = nextScene;
			}
		}
	}

	// �V�[���̍X�V
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