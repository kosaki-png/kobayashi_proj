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
	safe_delete(line[0].sprite);
	safe_delete(line[1].sprite);
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
			for (int i = 0; i < 2; i++)
			{
				// �����ʒu�ݒ�
				line[i].sprite = Sprite::Create(INTERVAL, { 0,0 });
				line[i].size = { 3000, 10 };
				line[i].position = { -3000, WINDOW_HEIGHT / 2 - 5 };
				line[i].speed = { 70.0f, 0 };
			}
			
			line[1].sprite->SetAnchorPoint({ 0.0f, 1.0f });
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
}

void IntervalScene::Update()
{
	isCover = false;

	if (isEffect)
	{
		// �G�t�F�N�g�I��
		if (startCnt > 180)
		{
			isEffect = false;
		}

		for (int i = 0; i < 2; i++)
		{
			if (startCnt >= 30 && startCnt < 90)
			{
				if (line[i].position.x <= WINDOW_WIDTH - 3000)
				{
					line[i].position.x += line[i].speed.x;
					line[i].position.y += line[i].speed.y;
				}
				if (line[i].position.x >= WINDOW_WIDTH - 3000)
				{
					if (width < WINDOW_HEIGHT / 2)
					{
						width += width / 8;
					}

					line[i].size = { 3000, width };
				}
			}
			if (startCnt >= 120)
			{
				if (width > 0)
				{
					width -= width / 8;
				}
				if (width <= 0)
				{
					width = 0;
				}
				line[i].size = { 3000, width };
			}

			if (startCnt == 90)
			{
				isCover = true;
			}
			line[i].sprite->SetPosition(line[i].position);
			line[i].sprite->SetSize(line[i].size);
		}
	}

	// �J�����X�V
	{
		camera->Update();
	}

	startCnt++;
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
			if (isEffect)
			{
				for (int i = 0; i < 2; i++)
				{
					line[i].sprite->Draw();
				}
			}
		}
		Sprite::PostDraw();
	}
}

void IntervalScene::Finalize()
{
}

void IntervalScene::Start()
{
	// �G�t�F�N�g������
	startCnt = 0;
	width = 10;

	for (int i = 0; i < 2; i++)
	{
		// �����ʒu�ݒ�
		line[i].size = { 3000, 10 };
		line[i].position = { -3000, WINDOW_HEIGHT / 2 - 5 };
		line[i].speed = { 70.0f, 0 };
	}

	isEffect = true;
}