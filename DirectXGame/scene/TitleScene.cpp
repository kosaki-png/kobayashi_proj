#include "TitleScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>
#include <thread>

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

	modelMngTitle->Load(23, "01_77");	// 23
	modelMngTitle->Load(43, "02_41");	// 43
	modelMngTitle->Load(63, "03_40");	// 63
	modelMngTitle->Load(83, "04_85");	// 83

	SetLockFlag(true);
}

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
	delete tmpSprite;
}

void TitleScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptr�`�F�b�N
	BaseScene::Initialize(dxCommon, input, audio);

	// �ėp�I������
	{
		// �J��������
		camera = new DebugCamera(WinApp::window_width, WinApp::window_height, input);
	
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
		}

		// �X�v���C�g�����ݒ�
		{
		}
	}

	// �񓯊����[�h�J�n
	if (!isLoadedTitle)
	{
		th = new std::thread(AsyncLoad);
	}

	// �J���������_���Z�b�g
	camera->SetTarget({ 0, -1, 0 });

	isGodray = true;
}

void TitleScene::Update()
{	
	// �񓯊����[�h��
	if (!GetLockFlag())
	{

	}
	else   // ���[�h�I����
	{
		// SPACE�Ŏ��̃V�[��
		if (input->TriggerKey(DIK_SPACE))
		{
			nextScene = new SelectScene();
		}
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

	camera->Update();

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
		Sprite::PreDraw(cmdList);
		{
			tmpSprite->Draw();
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
		}
		Sprite::PostDraw();
	}
}

void TitleScene::Finalize()
{
	if (!isLoadedTitle)
	{
		th->join();
	}
}
