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
	delete back;
	for (int i = 0; i < 4; i++)
	{
		delete trance[i].sprite;
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
			Sprite::LoadTexture(101, L"Resources/texture/interval_back.png");
			Sprite::LoadTexture(102, L"Resources/texture/interval_up.png");
			Sprite::LoadTexture(103, L"Resources/texture/interval_left.png");
			Sprite::LoadTexture(104, L"Resources/texture/interval_down.png");
			Sprite::LoadTexture(105, L"Resources/texture/interval_right.png");
		}

		// �X�v���C�g����
		{
			back = Sprite::Create(101, { 0,0 });
			back->SetAlpha(0);

			for (int i = 0; i < 4; i++)
			{
				trance[i].sprite = Sprite::Create(102 + i, { 0,0 });
				// �����ʒu�ݒ�
				if (i < 2)
				{
					trance[i].position = { 10000, -WINDOW_HEIGHT };
				}
				else
				{
					trance[i].position = { 10000,  WINDOW_HEIGHT };
				}

				trance[i].sprite->SetPosition(trance[i].position);
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

	if (isEffect)
	{
		for (int i = 0; i < 4; i++)
		{
			if (trance[i].position.y == 0)
			{
				trance[i].speed.x = 0.0f;
				trance[i].speed.y = 0.0f;
			}

			// 0.5�b�ォ��X�^�[�g
			if (startCnt == 30)
			{
				trance[0].speed.y = WINDOW_HEIGHT / 20.0f;
				trance[2].speed.y = -WINDOW_HEIGHT / 20.0f;
			}
			if (startCnt == 40)
			{
				trance[1].speed.y = WINDOW_HEIGHT / 20.0f;
				trance[3].speed.y = -WINDOW_HEIGHT / 20.0f;
			}

			//
			if (startCnt >= 100 && startCnt < 160)
			{
				alpha += 0.015f;
			}

			if (startCnt >= 160 && startCnt < 220)
			{
				alpha -= 0.015f;
			}

			// 0.5�b�ォ��X�^�[�g
			if (startCnt == 230)
			{
				trance[1].speed.y = -WINDOW_HEIGHT / 20.0f;
				trance[3].speed.y = WINDOW_HEIGHT / 20.0f;
			}
			if (startCnt == 250)
			{
				trance[0].speed.y = -WINDOW_HEIGHT / 20.0f;
				trance[2].speed.y = WINDOW_HEIGHT / 20.0f;
			}

			// ���x������W���X�V
			trance[i].position.x += trance[i].speed.x;
			trance[i].position.y += trance[i].speed.y;

			// ���W���Z�b�g
			trance[i].sprite->SetPosition(trance[i].position);

			back->SetAlpha(alpha);
		}

		// ���S�ɉB�ꂽ�^�C�~���O
		if (startCnt == 160)
		{
			isCover = true;
		}

		// �G�t�F�N�g�I��
		if (startCnt > 270)
		{
			isEffect = false;
		}
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
			if (isEffect)
			{
				back->Draw();
				for (int i = 3; i >= 0; i--)
				{
					trance[i].sprite->Draw();
				}
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
	alpha = 0.0f;

	for (int i = 0; i < 4; i++)
	{
		// �����ʒu�ݒ�
		if (i < 2)
		{
			trance[i].position = { 0, -WINDOW_HEIGHT };
		}
		else
		{
			trance[i].position = { 0,  WINDOW_HEIGHT };
		}
	}

	isEffect = true;
}