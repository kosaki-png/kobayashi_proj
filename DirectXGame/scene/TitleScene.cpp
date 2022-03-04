#include "TitleScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>
#include <thread>
#include <chrono>

using namespace DirectX;
using namespace SpriteData;

// �񓯊����[�h�p
ModelManager* modelMngTitle = ModelManager::GetInstance();
bool isLoadedTitle = false;
std::mutex isLoadedMutexTitle;

// �񓯊����[�h�p
void SetLockFlag(bool _)
{
	std::lock_guard<std::mutex>  lock(isLoadedMutexTitle);
	isLoadedTitle = true;
}

bool GetLockFlag()
{
	std::lock_guard<std::mutex>  lock(isLoadedMutexTitle);
	return isLoadedTitle;
}

// �񓯊����[�h�֐�
void AsyncLoad()
{
	// �Z���N�g�Ɏg���f�[�^�擾
	StageDataStorage::LoadData selectData = StageDataStorage::GetInstance()->GetDeSelectData();

	// ��񂩂�K�v�ȃ��f�������[�h
	for (int i = 0; i < selectData.modelName.size(); i++)
	{
		modelMngTitle->Load(selectData.firstNum + i, selectData.modelName[i]);
	}

	modelMngTitle->Load(100, "01_77");	// 23
	modelMngTitle->Load(101, "02_41");	// 43
	modelMngTitle->Load(102, "03_40");	// 63
	modelMngTitle->Load(103, "04_85");	// 83

	SetLockFlag(true);
}

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
	safe_delete(camera);
	safe_delete(tmpSprite);
	safe_delete(fadeSprite);
}

void TitleScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
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
			// �X�v���C�g�����[�h���Ă��Ȃ��Ȃ炷��
			if (!SpriteLoader::GetTitleFlag())
			{
				SpriteLoader::LoadTitleSprite();
			}
		}

		// �X�v���C�g����
		{
			tmpSprite = Sprite::Create(TITLE, { 0,0 });
			fadeSprite = Sprite::Create(FADE, { 0,0 });
		}

		// �X�v���C�g�����ݒ�
		{
			fadeSprite->SetPosition({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 });
			fadeSprite->SetAnchorPoint({ 0.5f, 0.5f });
		}
	}

	// �񓯊����[�h�J�n
	if (!isLoadedTitle)
	{
		th = new std::thread(AsyncLoad);
	}

	// �J���������_���Z�b�g
	camera->SetTarget({ 0, -1, 0 });

	// �e�N���X������
	{
	}

	isGodray = true;
	trans = 0;
}

void TitleScene::Update()
{	
	// ���[�h�I����
	if (GetLockFlag())
	{
		// SPACE�Ŏ��̃V�[��
		if (input->TriggerKey(DIK_SPACE))
		{
			nextScene = new SelectScene();
		}	
	}

	// �^�C�g�����o
	{
		if (fadeSize.x <= 2000)
		{
			fadeSize.x += 30.0f;
			fadeSize.y += 30.0f;
		}
		else
		{
			fadeAlpha -= 0.005f;
		}
	}

	// �}�E�X�|�C���g
	{
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(FindWindowA(nullptr, "seeker"), &p);
		mousePos = { (float)p.x, (float)p.y };
	}

	camera->Update();

	// 3D�I�u�W�F�N�g�X�V
	{
	}

	// �X�v���C�g�X�V
	{
		fadeSprite->SetSize(fadeSize);
		fadeSprite->SetAlpha(fadeAlpha);
	}

}

void TitleScene::Draw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	// �w�i�X�v���C�g�`��
	{
		Sprite::PreDraw(cmdList);
		{
			if (fadeSize.x >= 2000)
			{
				tmpSprite->Draw();
			}
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
			fadeSprite->Draw();
		}
		Sprite::PostDraw();
	}
}

void TitleScene::FrontDraw()
{
	// �R�}���h���X�g�̎擾
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

	// �X�v���C�g�`��
	Sprite::PreDraw(cmdList);
	{

	}
	Sprite::PostDraw();
}

void TitleScene::Finalize()
{
	if (!isLoadedTitle)
	{
		th->join();
	}
}
