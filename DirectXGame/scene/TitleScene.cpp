#include "TitleScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>
#include <thread>

using namespace DirectX;

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
	//�_�~�[��10�b�҂�
	/*auto sleepTime = std::chrono::seconds(10);
	std::this_thread::sleep_for(sleepTime);*/

	modelMngTitle->Load(13, "01_77");	// 13
	modelMngTitle->Load(33, "02_41");	// 33
	modelMngTitle->Load(53, "03_40");	// 53
	modelMngTitle->Load(73, "04_85");	// 73

	SetLockFlag(true);
}

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

	// �񓯊����[�h�J�n
	if (!isLoadedTitle)
	{
		th = new std::thread(AsyncLoad);
	}

	// �J���������_���Z�b�g
	camera->SetTarget({ 0, -1, 0 });
	camera->SetDistance(25.0f);

}

void TitleScene::Update()
{
	// �R���g���[���̍X�V
	xinput.Update();
	
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

	// �p�[�e�B�N������
	//CreateParticles();

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

void TitleScene::Finalize()
{
	if (!isLoadedTitle)
	{
		th->join();
	}
}
