#include "EndScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>

using namespace DirectX;

EndScene::EndScene()
{
}

EndScene::~EndScene()
{
	safe_delete(tmpSprite);
}

void EndScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptr�`�F�b�N
	BaseScene::Initialize(dxCommon, input, audio);

	// �J��������
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height, input);

	// �X�v���C�g�����ݒ�
	{
		// �X�v���C�g�p�e�N�X�`���ǂݍ���
		{
			Sprite::LoadTexture(1, L"Resources/texture/clear.png");
		}

		// �X�v���C�g����
		{
			tmpSprite = Sprite::Create(1, { 0,0 });
		}

		// �X�v���C�g�����ݒ�
		{
		}
	}

	// FBX�I�u�W�F�N�g�����ݒ�
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

	// �J���������_���Z�b�g
	camera->SetTarget({ 0, 1, 0 });

	isGodray = true;
}

void EndScene::Update()
{
	// �X�y�[�X�Ŏw��̃V�[����
	if (input->TriggerKey(DIK_SPACE))
	{
		// �^�C�g���V�[����
		nextScene = new TitleScene();
	}

	// ESCAPE�ŃQ�[���I��
	if (input->PushKey(DIK_ESCAPE))
	{
		PostQuitMessage(0);
		EndScene::~EndScene();
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

	camera->Update();

	// 3D�I�u�W�F�N�g�X�V
	{
	}
}

void EndScene::Draw()
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
	}

	// �O�i�X�v���C�g�`��
	{
		// �O�i�X�v���C�g�`��O����
		Sprite::PreDraw(cmdList);

		// �X�v���C�g�`��㏈��
		Sprite::PostDraw();
	}
}

void EndScene::Finalize()
{
}
