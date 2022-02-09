#include "SelectScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>

using namespace DirectX;
using namespace SpriteData;

SelectScene::SelectScene()
{
}

SelectScene::~SelectScene()
{
	for (auto x : map)
	{
		delete x;
	}
	delete back;
}

void SelectScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptr�`�F�b�N
	BaseScene::Initialize(dxCommon, input, audio);

	// �ėp�I������
	{
		// �J��������
		camera = new FixedCamera(WinApp::window_width, WinApp::window_height);
		
		// �f�o�C�X���Z�b�g
		Fbx::SetDevice(dxCommon->GetDevice());
		// �J�������Z�b�g
		Fbx::SetCamera(camera);
		// �O���t�B�b�N�X�p�C�v���C������
		Fbx::CreateGraphicsPipeline();
	}

	// �X�v���C�g�����ݒ�
	{
		// �X�v���C�g�p�e�N�X�`���ǂݍ���
		{
			// ���[�h���Ă��Ȃ��Ȃ炷��
			if (!SpriteLoader::GetSelectFlag())
			{
				SpriteLoader::LoadSelectSprite();
			}
		}

		// �X�v���C�g����
		{
		}

		// �X�v���C�g�����ݒ�
		{
		}
	}

	// FBX�I�u�W�F�N�g�����ݒ�
	{
		// �Z���N�g�p�}�b�v
		for (int i = 0; i < 4; i++)
		{
			map[i] = new Fbx();
			map[i]->Initialize();
			map[i]->SetModel(ModelManager::GetInstance()->GetModel(i + stageData->GetDeSelectData().firstNum + 1));
			map[i]->SetFog(false);
		}

		// �w�i
		back = new Fbx();
		back->Initialize();
		back->SetModel(ModelManager::GetInstance()->GetModel(stageData->GetDeSelectData().firstNum));
		back->SetFog(false);
		back->SetPosition({ 0,0,300 });
		back->SetScale({ 5,5,8 });
	}

	// �J����������
	{
		// �J���������_���Z�b�g
		camera->SetTarget({ 0, 10, 0 });
		camera->SetEye({ 0,200,400 });
	}

	// �e�N���X�̏�����
	{
	}

	isGodray = true;
}

void SelectScene::Update()
{
	stop = false;

	if (!stop)
	{
		// �V�[���ڍs
		if (input->TriggerKey(DIK_0))
		{
			// �I�������}�b�v�ŃQ�[���V�[����
			nextScene = new LoadScene(0);
		}
		if (input->TriggerKey(DIK_1))
		{
			// �I�������}�b�v�ŃQ�[���V�[����
			nextScene = new LoadScene(1);
		}
		if (input->TriggerKey(DIK_2))
		{
			// �I�������}�b�v�ŃQ�[���V�[����
			nextScene = new LoadScene(2);
		}
		if (input->TriggerKey(DIK_3))
		{
			// �I�������}�b�v�ŃQ�[���V�[����
			nextScene = new LoadScene(3);
		}

		// ESCAPE�ŃQ�[���I��
		if (input->PushKey(DIK_ESCAPE))
		{
			SelectScene::~SelectScene();
			PostQuitMessage(0);
		}

		// �}�E�X�|�C���g
		{
			static POINT p;
			GetCursorPos(&p);
			WinApp* win = nullptr;
			win = new WinApp();
			ScreenToClient(FindWindowA(nullptr, "Hooper"), &p);
			mousePos = { (float)p.x, (float)p.y };
		}
	}
	camera->Update();

	// 3D�I�u�W�F�N�g�X�V
	{
		for (int i = 0; i < 4; i++)
		{
			map[i]->Update();
		}

		back->Update();
	}

	// �e�N���X�̍X�V
	{}

}

void SelectScene::Draw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	// �w�i�X�v���C�g�`��
	{
		// �w�i�X�v���C�g�`��O����
		Sprite::PreDraw(cmdList);

		// �X�v���C�g�`��㏈��
		Sprite::PostDraw();
		// �[�x�o�b�t�@�N���A
		dxCommon->ClearDepthBuffer();
	}

	// 3D�`��
	{
		back->Draw(cmdList);

		for (int i = 0; i < 4; i++)
		{
			map[i]->Draw(cmdList);
		}
	}

	// �O�i�X�v���C�g�`��
	{
		// �O�i�X�v���C�g�`��O����
		Sprite::PreDraw(cmdList);

		// �X�v���C�g�`��㏈��
		Sprite::PostDraw();
	}
}

void SelectScene::Finalize()
{
}
