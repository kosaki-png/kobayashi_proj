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
	// �ŏ��̃V�[��
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

	// �ŏ��̃V�[���̏�����
	scene->Initialize(this->dxCommon, this->input, this->audio);
	interval->Initialize(this->dxCommon, this->input, this->audio);

	postEffect->SetGodray(scene->GetGodrayFlag());
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
				interval->SetTrans(scene->GetTrans());
				interval->Start();
			}
			
			if (interval->GetIsCover())
			{
				// ���̃V�[�����폜
				delete scene;

				// ���Ɏw�肵���V�[����������
				nextScene->Initialize(dxCommon, input, audio);

				postEffect->SetGodray(nextScene->GetGodrayFlag());

				// ���݂̃V�[���ɓK�p
				scene = nextScene;
			}
		}
	}

	// �V�[���̍X�V
	scene->Update();
	interval->Update();

	// �S�b�h���C�̍X�V
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
	// �|�X�g�G�t�F�N�g�̕`��
	postEffect->Draw(dxCommon->GetCommandList());
	scene->FrontDraw();
	interval->Draw();
}

void SceneManager::Finalize()
{
	scene->Finalize();
	interval->Finalize();
}
