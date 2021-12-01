#include "TitleScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>
#include <thread>

using namespace DirectX;

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
	safe_delete(tmpSprite);
}

void TitleScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptr�`�F�b�N
	BaseScene::Initialize(dxCommon, input, audio);

	// �ėp�I������
	{
		// �J��������
		camera = new DebugCamera(WinApp::window_width, WinApp::window_height, input);

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
			Sprite::LoadTexture(1, L"Resources/texture/title_tmp.png");
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
	camera->SetTarget({ 0, -1, 0 });
	camera->SetDistance(25.0f);

	fade->Initialize();

	// 
	if (!nextSceneFlag)
	{

	}
	
	/*texCollision = new TexCollision();
	texCollision->LoadTexture(1, L"Resources/texture/test.png");
	static XMFLOAT4 testColor;
	testColor = texCollision->GetPixelColor(1, 1, 0);

	assert(1);*/
}

void TitleScene::Update()
{
	// �R���g���[���̍X�V
	xinput.Update();
	stop = false;
	if (!stop)
	{
		// �X�y�[�X�Ŏw��̃V�[����
		if (input->TriggerKey(DIK_SPACE) || xinput.TriggerButtom(0, xinput_A))
		{
			/*fade->InStart(false);
			nextSceneFlag = true;*/
			// �Z���N�g�V�[����
			nextScene = new SelectScene();
		}

		// ESCAPE�ŃQ�[���I��
		if (input->PushKey(DIK_ESCAPE))
		{
			TitleScene::~TitleScene();
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

		// �p�[�e�B�N������
		//CreateParticles();

		// 
		if (input->TriggerKey(DIK_1))
		{
			fade->InStart();
		}
		if (input->TriggerKey(DIK_2))
		{
			fade->OutStart();
		}
	}

	fade->Update();

	lightGroup->Update();
	camera->Update();
	particleMan->Update();

	// 3D�I�u�W�F�N�g�X�V
	{
	}
}

void TitleScene::Draw()
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
		// 3D�I�u�W�F�N�g�̕`��
		Object3d::PreDraw(cmdList);

		/// <summary>
		/// ������3D�I�u�W�F�N�g�̕`�揈����ǉ�
		/// </summary>

		Object3d::PostDraw();

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

		fade->Draw();

		// �X�v���C�g�`��㏈��
		Sprite::PostDraw();
	}
}

void TitleScene::Finalize()
{
}
