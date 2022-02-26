#include "EndScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>

using namespace DirectX;
using namespace SpriteData;

EndScene::EndScene()
{
}

EndScene::~EndScene()
{
	safe_delete(camera);
	safe_delete(tmpSprite);
	safe_delete(frame);
	safe_delete(cursor);
}

void EndScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptr�`�F�b�N
	BaseScene::Initialize(dxCommon, input, audio);

	// �J��������
	camera = new OrbitCamera(WinApp::window_width, WinApp::window_height);

	// �X�v���C�g�����ݒ�
	{
		// �X�v���C�g�p�e�N�X�`���ǂݍ���
		{
			// ���[�h���Ă��Ȃ��Ȃ炷��
			if (!SpriteLoader::GetEndFlag())
			{
				SpriteLoader::LoadEndSprite();
			}
		}

		// �X�v���C�g����
		{
			tmpSprite = Sprite::Create(CLEAR, { 0,0 });
			frame = Sprite::Create(RESULT_FRAME, { 0,0 });
			cursor = Sprite::Create(RESULT_CURSOR, { 0,0 });
		}

		// �X�v���C�g�����ݒ�
		{
			cursor->SetAnchorPoint({ 0.5f, 0.5f });
			cursor->SetPosition({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 });
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
	trans = 0;
}

void EndScene::Update()
{
	// �}�E�X�|�C���g
	{
		static POINT p;
		GetCursorPos(&p);
		WinApp* win = nullptr;
		win = new WinApp();
		ScreenToClient(FindWindowA(nullptr, "Hooper"), &p);
		mousePos = { (float)p.x, (float)p.y };
	}

	if (cursorFlip)
	{
		// �J�[�\���ړ��i�L�[�j
		if (input->TriggerKey(DIK_LEFT) || input->TriggerKey(DIK_A))
		{
			cursorFlip = false;
			cursor->SetIsFlipX(cursorFlip);
		}

		// �X�y�[�X�Ŏw��̃V�[����
		if (input->TriggerKey(DIK_SPACE))
		{
			// �^�C�g���V�[����
			nextScene = new TitleScene();
		}
	}
	else
	{
		// �J�[�\���ړ��i�L�[�j
		if (input->TriggerKey(DIK_RIGHT) || input->TriggerKey(DIK_D))
		{
			cursorFlip = true;
			cursor->SetIsFlipX(cursorFlip);
		}

		// �X�y�[�X�Ŏw��̃V�[����
		if (input->TriggerKey(DIK_SPACE))
		{
			// �Z���N�g�V�[����
			nextScene = new SelectScene();
		}
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
		// �w�i�X�v���C�g�`��
		Sprite::PreDraw(cmdList);
		{
			tmpSprite->Draw();
		}
		Sprite::PostDraw();

		// �[�x�o�b�t�@�̃N���A
		dxCommon->ClearDepthBuffer();
	}

	// 3D�`��
	{
	}

	// �O�i�X�v���C�g�`��
	{
		// �O�i�X�v���C�g�`��
		Sprite::PreDraw(cmdList);
		{

		}
		Sprite::PostDraw();
	}
}

void EndScene::FrontDraw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	// �X�v���C�g�`��
	Sprite::PreDraw(cmdList);
	{
		frame->Draw();
		cursor->Draw();
	}
	Sprite::PostDraw();
}

void EndScene::Finalize()
{
}
