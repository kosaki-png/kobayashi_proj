#include "LoadScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>

using namespace DirectX;

// �񓯊����[�h�p
bool isLoadedLoad = false;
std::mutex isLoadedMutexLoad;
// ���f���Ǘ��N���X�̃C���X�^���X�擾
ModelManager* modelMngLoad = ModelManager::GetInstance();

// ���[�h�o�[����
float loadRatio = 0;
const int LOAD_MODEL_COUNT = 12;	// �ǂݍ��ރI�u�W�F�N�g�̐�
const float LOAD_RATIO = 1.0f / LOAD_MODEL_COUNT;	// �I�u�W�F�N�g��ǂݍ��񂾎��ɐi�ފ���

// �񓯊����[�h�p
void LoadSetLockFlag(bool _)
{
	std::lock_guard<std::mutex>  lock(isLoadedMutexLoad);
	isLoadedLoad = true;
}

bool LoadGetLockFlag()
{
	std::lock_guard<std::mutex>  lock(isLoadedMutexLoad);
	return isLoadedLoad;
}

// ���[�h�o�[��i�߂�
void AddRatio(float rate)
{
	loadRatio += rate;
}

float GetRatio()
{
	return loadRatio;
}

// �񓯊����[�h�֐�
void IntervalAsyncLoad()
{
	//�_�~�[��10�b�҂�
	/*auto sleepTime = std::chrono::seconds(10);
	std::this_thread::sleep_for(sleepTime);*/

	// ���f�������[�h���Ċ����𑝂₷
	modelMngLoad->Load(0, "player");	AddRatio(LOAD_RATIO);	// 0
	modelMngLoad->Load(1, "01_87");		AddRatio(LOAD_RATIO);	// 1
	modelMngLoad->Load(2, "01_88");		AddRatio(LOAD_RATIO);	// 2
	modelMngLoad->Load(3, "01_89");		AddRatio(LOAD_RATIO);	// 3
	//modelMng->Load("01_77");	// 4
	modelMngLoad->Load(5, "01_78");		AddRatio(LOAD_RATIO);	// 5
	modelMngLoad->Load(6, "01_79");		AddRatio(LOAD_RATIO);	// 6
	modelMngLoad->Load(7, "01_67");		AddRatio(LOAD_RATIO);	// 7
	modelMngLoad->Load(8, "01_68");		AddRatio(LOAD_RATIO);	// 8
	modelMngLoad->Load(9, "01_69");		AddRatio(LOAD_RATIO);	// 9
	modelMngLoad->Load(10, "floor");	AddRatio(LOAD_RATIO);	// 10
	modelMngLoad->Load(11, "skydome");	AddRatio(LOAD_RATIO);	// 11
	modelMngLoad->Load(12, "Enemy");	AddRatio(LOAD_RATIO);	// 12

	// ���[�h�y��
	//modelMngLoad->Load(0, "player");	// 0
	//modelMngLoad->Load(1, "player");	// 1
	//modelMngLoad->Load(2, "player");	// 2
	//modelMngLoad->Load(3, "player");	// 3
	////modelMng->Load("01_77");	// 4
	//modelMngLoad->Load(5, "player");	// 5
	//modelMngLoad->Load(6, "player");	// 6
	//modelMngLoad->Load(7, "player");	// 7
	//modelMngLoad->Load(8, "player");	// 8
	//modelMngLoad->Load(9, "player");	// 9
	//modelMngLoad->Load(10, "player");	// 10
	//modelMngLoad->Load(11, "player");	// 11
	//modelMngLoad->Load(12, "player");	// 12

	LoadSetLockFlag(true);
}

LoadScene::LoadScene()
{
}

LoadScene::~LoadScene()
{
}

void LoadScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
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
			Sprite::LoadTexture(1, L"Resources/texture/loading.png");
			Sprite::LoadTexture(2, L"Resources/texture/loaded.png");
			Sprite::LoadTexture(3, L"Resources/texture/load_bar.png");
			Sprite::LoadTexture(4, L"Resources/texture/load_bar_white.png");
		}

		// �X�v���C�g����
		{
			loading = Sprite::Create(1, { 0,0 });
			loaded = Sprite::Create(2, { 0,0 });
			loadBar = Sprite::Create(3, { 0,0 });
			loadBarWhite = Sprite::Create(4, { 243,603 });
		}

		// �X�v���C�g�����ݒ�
		{
		}
	}

	// FBX�I�u�W�F�N�g�����ݒ�
	{
		kogakuin = new Fbx();
		kogakuin->Initialize();
		kogakuin->SetModel(modelMngLoad->GetModel(4));
		kogakuin->SetPosition({ -1130 / 2, 0, -925 - 925 / 2 });
	}

	// �J���������ݒ�
	{
		//camera->SetMouseFlag(false);
	}

	// �񓯊����[�h�J�n
	if (!isLoadedLoad)
	{
		th = new std::thread(IntervalAsyncLoad);
	}
}

void LoadScene::Update()
{
	// �񓯊����[�h��
	if (!LoadGetLockFlag())
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

	// ���[�h�o�[���Z
	float bar = GetRatio() * 800.0f;
	loadBarWhite->SetPosUV({ -GetRatio() + 1.0f, 0 });

	// FBX�X�V
	{
		kogakuin->Update();
	}

	// �J�����X�V
	{
		camera->Update();
	}

	lightGroup->Update();
	particleMan->Update();
}

void LoadScene::Draw()
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
			if (!LoadGetLockFlag())
			{

			}
			else   // ���[�h�I����
			{

			}

			kogakuin->Draw(cmdList, true);
		}
		Object3d::PostDraw();

		// �p�[�e�B�N���̕`��
		particleMan->Draw(cmdList);
	}

	// �O�i�X�v���C�g�`��
	{
		Sprite::PreDraw(cmdList);
		{
			// ���[�h�o�[
			loadBarWhite->Draw();
			loadBar->Draw();
			// �񓯊����[�h��
			if (!LoadGetLockFlag())
			{
				loading->Draw();
			}
			else   // ���[�h�I����
			{
				loaded->Draw();
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

void LoadScene::Finalize()
{
	if (!isLoadedLoad)
	{
		th->join();
	}
}