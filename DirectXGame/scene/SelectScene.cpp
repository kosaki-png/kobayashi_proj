#include "SelectScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>

using namespace DirectX;

SelectScene::SelectScene()
{
}

SelectScene::~SelectScene()
{
	safe_delete(tmpSprite);
}

void SelectScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptr�`�F�b�N
	BaseScene::Initialize(dxCommon, input, audio);

	// �ėp�I������
	{
		// �J��������
		camera = new MainCamera(WinApp::window_width, WinApp::window_height, input);

		// �f�o�b�O�e�L�X�g�p�e�N�X�`���ǂݍ���
		if (!Sprite::LoadTexture(texNumber, L"Resources/debugfont.png")) {
			assert(0);
			return;
		}
		// �f�o�b�O�e�L�X�g������
		text = Text::GetInstance();
		text->Initialize(texNumber);

		// ���C�g����
		lightGroup = LightGroup::Create();

		// �p�[�e�B�N���}�l�[�W������
		particleMan = ParticleManager::GetInstance();
		particleMan->SetCamera(camera);
	}

	// �X�v���C�g�����ݒ�
	{
		// �X�v���C�g�p�e�N�X�`���ǂݍ���
		{
			Sprite::LoadTexture(1, L"Resources/texture/star.png");
		}

		// �X�v���C�g����
		{
			tmpSprite = Sprite::Create(1, { 0,0 });
		}

		// �X�v���C�g�����ݒ�
		{
		}
	}

	// OBJ�I�u�W�F�N�g�����ݒ�
	{
		// ���f���ǂݍ���
		{
		}

		// 3D�I�u�W�F�N�g����
		{
		}

		// 3D�I�u�W�F�N�g�����ݒ�
		{
		}
	}

	// FBX�I�u�W�F�N�g�����ݒ�
	{
		// ���f������
		{
			for (int i = 0; i < 4; i++)
			{
				map[i] = new Fbx();
				map[i]->Initialize();
				map[i]->SetModel(ModelManager::GetInstance()->GetModel(i * 20 + 13));
			}
		}
	}

	// �J���������_���Z�b�g
	camera->SetTarget({ 0, 1, 0 });
	//camera->SetDistance(10.0f);

	// �e�N���X�̏�����
	{
	}
}

void SelectScene::Update()
{
	stop = false;

	if (!stop)
	{
		// �R���g���[���̍X�V
		xinput.Update();

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

	lightGroup->Update();
	camera->Update();
	particleMan->Update();

	// 3D�I�u�W�F�N�g�X�V
	{
		for (int i = 0; i < 4; i++)
		{
			map[i]->Update();
		}
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

		/// <summary>
		/// �����ɔw�i�X�v���C�g�̕`�揈����ǉ�
		/// </summary>
		tmpSprite->Draw();

		// �X�v���C�g�`��㏈��
		Sprite::PostDraw();
		// �[�x�o�b�t�@�N���A
		dxCommon->ClearDepthBuffer();
	}

	// 3D�`��
	{
		for (int i = 0; i < 4; i++)
		{
			map[i]->Draw(cmdList, true);
		}

		// �p�[�e�B�N���̕`��
		particleMan->Draw(cmdList);
	}

	// �O�i�X�v���C�g�`��
	{
		// �O�i�X�v���C�g�`��O����
		Sprite::PreDraw(cmdList);

		/// <summary>
		/// �����ɑO�i�X�v���C�g�̕`�揈����ǉ�
		/// </summary>

		// �f�o�b�O�e�L�X�g�̕`��
		text->DrawAll(cmdList);

		// �X�v���C�g�`��㏈��
		Sprite::PostDraw();
	}
}

void SelectScene::Finalize()
{
}
