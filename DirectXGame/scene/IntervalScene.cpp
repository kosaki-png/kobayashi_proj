#include "IntervalScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>

using namespace DirectX;

// �񓯊����[�h�p
bool isLoaded = false;
std::mutex isLoadedMutex;
// ���f���Ǘ��N���X�̃C���X�^���X�擾
ModelManager* modelMng = ModelManager::GetInstance();

// �񓯊����[�h�p
void SetLockFlag(bool _)
{
	std::lock_guard<std::mutex>  lock(isLoadedMutex);
	isLoaded = true;
}

bool GetLockFlag()
{
	std::lock_guard<std::mutex>  lock(isLoadedMutex);
	return isLoaded;
}

// �񓯊����[�h�֐�
void AsyncLoad()
{
	//�_�~�[��10�b�҂�
	/*auto sleepTime = std::chrono::seconds(10);
	std::this_thread::sleep_for(sleepTime);*/

	modelMng->Load("player");	// 0
	modelMng->Load("01_87");	// 1
	modelMng->Load("01_88");	// 2
	modelMng->Load("01_89");	// 3
	modelMng->Load("01_77");	// 4
	modelMng->Load("01_78");	// 5
	modelMng->Load("01_79");	// 6
	modelMng->Load("01_67");	// 7
	modelMng->Load("01_68");	// 8
	modelMng->Load("01_69");	// 9
	modelMng->Load("floor");	// 10
	modelMng->Load("skydome");	// 11
	//modelMng->Load("player");	// 1
	//modelMng->Load("player");	// 2
	//modelMng->Load("player");	// 3
	//modelMng->Load("player");	// 4
	//modelMng->Load("player");	// 5
	//modelMng->Load("player");	// 6
	//modelMng->Load("player");	// 7
	//modelMng->Load("player");	// 8
	//modelMng->Load("player");	// 9
	//modelMng->Load("player");	// 10
	//modelMng->Load("player");	// 11

	SetLockFlag(true);
}

IntervalScene::IntervalScene()
{
}

IntervalScene::~IntervalScene()
{
}

void IntervalScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
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
			Sprite::LoadTexture(1, L"Resources/texture/load.png");
			Sprite::LoadTexture(2, L"Resources/texture/loaded.png");
		}

		// �X�v���C�g����
		{
			load = Sprite::Create(1, { 0,0 });
			loadCircle = Sprite::Create(2, { 0,0 });
		}

		// �X�v���C�g�����ݒ�
		{
		}
	}

	// �񓯊����[�h�J�n
	if (!isLoaded)
	{
		th = new std::thread(AsyncLoad);
	}
}

void IntervalScene::Update()
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
			nextScene = new GameScene();
		}
	}

	lightGroup->Update();
	particleMan->Update();
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
			// �񓯊����[�h��
			if (!GetLockFlag())
			{

			}
			else   // ���[�h�I����
			{

			}
		}
		Object3d::PostDraw();

		// �p�[�e�B�N���̕`��
		particleMan->Draw(cmdList);
	}

	// �O�i�X�v���C�g�`��
	{
		Sprite::PreDraw(cmdList);
		{
			// �񓯊����[�h��
			if (!GetLockFlag())
			{
				load->Draw();
			}
			else   // ���[�h�I����
			{
				loadCircle->Draw();
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
	if (!isLoaded)
	{
		th->join();
	}
}
