#include "IntervalScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>

using namespace DirectX;

IntervalScene::IntervalScene()
{
}

IntervalScene::~IntervalScene()
{
	for (int i = 0; i < 6; i++)
	{
		delete trance[i].trance;
	}
}

void IntervalScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptr�`�F�b�N
	BaseScene::Initialize(dxCommon, input, audio);

	// �ėp�I������
	{
		// �J��������
		camera = new OrbitCamera(WinApp::window_width, WinApp::window_height);

		// 3D�I�u�W�F�N�g�ɃJ�������Z�b�g
		Object3d::SetCamera(camera);

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
		// 3D�I�u�G�N�g�Ƀ��C�g���Z�b�g
		Object3d::SetLightGroup(lightGroup);

		// �f�o�C�X���Z�b�g
		Fbx::SetDevice(dxCommon->GetDevice());
		// �J�������Z�b�g
		Fbx::SetCamera(camera);
		// �O���t�B�b�N�X�p�C�v���C������
		Fbx::CreateGraphicsPipeline();

		// �p�[�e�B�N���}�l�[�W������
		particleMan = ParticleManager::GetInstance();
		particleMan->SetCamera(camera);

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
			Sprite::LoadTexture(100, L"Resources/texture/trance.png");
		}

		// �X�v���C�g����
		{
			for (int i = 0; i < 6; i++)
			{
				trance[i].trance = Sprite::Create(100, { 0,0 });
				trance[i].position = { i * 320.0f - 160.0f, 720.0f };
			}
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

	// ����
	for (int i = 0; i < 6; i++)
	{
		// �ړ�����
		if (trance[i].position.y <= -720 || trance[i].position.y >= 0)
		{
			if (startCnt < 130)
			{
				trance[i].speed.x = 0.0f;
				trance[i].speed.y = 0.0f;
			}
		}

		// ��莞�Ԃňړ��ʕύX
		// �ォ��
		if (startCnt == 60 / 6 * i + 30)
		{
			trance[i].speed.x = -320.0f / 30;
			trance[i].speed.y = 20.0f;
		}
		// ���E��
		if (startCnt == 150)
		{
			for (int i = 0; i < 6; i++)
			{
				if (i < 3)
				{
					trance[i].speed.x = -20;
				}
				else
				{
					trance[i].speed.x = +20;
				}
			}
		}

		// �ړ��ʓK�p
		trance[i].position.x += trance[i].speed.x;
		trance[i].position.y += trance[i].speed.y;
		trance[i].trance->SetPosition({ trance[i].position });
	}

	if (startCnt == 130)
	{
		isCover = true;
	}

	if (startCnt > 250)
	{
		isEffect = false;
	}

	// �J�����X�V
	{
		camera->Update();
	}

	lightGroup->Update();
	particleMan->Update();

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
		Object3d::PreDraw(cmdList);
		{
			
		}
		Object3d::PostDraw();

		// �p�[�e�B�N���̕`��
		particleMan->Draw(cmdList);
	}

	// �O�i�X�v���C�g�`��
	{
		Sprite::PreDraw(cmdList);
		{
			for (int i = 0; i < 6; i++)
			{
				trance[i].trance->Draw();
			}

			// �f�o�b�O�e�L�X�g�̕`��
			text->DrawAll(cmdList);
		}
		Sprite::PostDraw();
	}

	// ImGui�`��
	{
		/*ImGui::Begin("OPTION");
		ImGui::SetWindowSize(ImVec2(100, 100));
		ImGui::SliderFloat("���x", &sence, 0.01f, 5.0f);
		ImGui::End();*/
	}
}

void IntervalScene::Finalize()
{
}

void IntervalScene::Start()
{
	// �G�t�F�N�g������
	startCnt = 0;
	// �ʒu������
	for (int i = 0; i < 6; i++)
	{
		trance[i].position = { i * 320.0f - 160.0f, -720.0f };
	}
	isEffect = true;
}