#include "IntervalScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>

using namespace DirectX;
using namespace SpriteData;

IntervalScene::IntervalScene()
{
}

IntervalScene::~IntervalScene()
{
	safe_delete(camera);
	safe_delete(transition);
}

void IntervalScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptr�`�F�b�N
	BaseScene::Initialize(dxCommon, input, audio);

	// �ėp�I������
	{
		// �J��������
		camera = new OrbitCamera(WinApp::window_width, WinApp::window_height);

		// �f�o�C�X���Z�b�g
		Fbx::SetDevice(dxCommon->GetDevice());
		// �J�������Z�b�g
		Fbx::SetCamera(camera);
		// �O���t�B�b�N�X�p�C�v���C������
		Fbx::CreateGraphicsPipeline();

		// �񓯊����[�h�p
		auto count = std::thread::hardware_concurrency();
		if (count < 3)
		{
			assert(1);
		}
	}

	// �X�v���C�g�����ݒ�
	{
		// �X�v���C�g�p�e�N�X�`���ǂݍ���
		{
			// ���[�h���Ă��Ȃ��Ȃ炷��
			if (!SpriteLoader::GetIntervalFlag())
			{
				SpriteLoader::LoadIntervalSprite();
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
		
	}

	// �J���������ݒ�
	{
		//camera->SetMouseFlag(false);
	}

	// �e�N���X������
	{
		transition = new Extend();
		//transition = new Gradually(false);
		transition->Initialize();
	}
}

void IntervalScene::Update()
{
	transition->Update();

	// �J�����X�V
	{
		camera->Update();
	}
}

void IntervalScene::Draw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	// �w�i�X�v���C�g�`��
	{
		Sprite::PreDraw(cmdList);
		{

		}
		Sprite::PostDraw();

		// �[�x�o�b�t�@�N���A
		dxCommon->ClearDepthBuffer();
	}

	// 3D�I�u�W�F�N�g�`��
	{
	}

	// �O�i�X�v���C�g�`��
	{
		Sprite::PreDraw(cmdList);
		{
			transition->Draw();
		}
		Sprite::PostDraw();
	}
}

void IntervalScene::Finalize()
{
}

void IntervalScene::Start()
{
	transition->Start();
}