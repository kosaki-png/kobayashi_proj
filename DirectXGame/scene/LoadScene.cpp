#include "LoadScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>

using namespace DirectX;

// ���f���Ǘ��N���X�̃C���X�^���X�擾
ModelManager* modelMngLoad = ModelManager::GetInstance();

const int STAGE_COUNT = 3;		// �X�e�[�W�̐�

const int LOAD_DEF_MODEL_CNT = 3;		// �f�t�H���g�Ń��[�h���郂�f���̐�
const int LOAD_STAGE_MODEL_CNT = 10;	// �X�e�[�W			�V

// ���[�h�o�[����
float loadRatio[STAGE_COUNT] = { 0, 0, 0 };
int modelCnt = 0;	// �ǂݍ��ރI�u�W�F�N�g�̐�
float ratioPiece = 0;	// �I�u�W�F�N�g��ǂݍ��񂾎��ɐi�ފ���

// ���[�h�o�[��i�߂�
void AddRatio(int stage)
{
	loadRatio[stage] += ratioPiece;
}
float GetRatio(int stage)
{
	return loadRatio[stage];
}

#pragma region �f�t�H���g���[�h

#pragma region �g���K�[�n

bool loadDefault = false;
std::mutex mutexDefault;

void SetLoadDefault(bool flag)
{
	std::lock_guard<std::mutex>  lock(mutexDefault);
	loadDefault = flag;
}
bool GetLoadDefault()
{
	std::lock_guard<std::mutex>  lock(mutexDefault);
	return loadDefault;
}

#pragma endregion

void LoadDefault(int stage)
{
	//�_�~�[��10�b�҂�
	/*auto sleepTime = std::chrono::seconds(10);
	std::this_thread::sleep_for(sleepTime);*/

	// ���f�������[�h���Ċ����𑝂₷
	modelMngLoad->Load(0, "player");			AddRatio(stage);	// 0
	modelMngLoad->Load(1, "Enemy");				AddRatio(stage);	// 1
	modelMngLoad->Load(2, "Enemy_circle");		AddRatio(stage);	// 2

	SetLoadDefault(true);
}

#pragma endregion

#pragma region �X�e�[�W���[�h

#pragma region �g���K�[�n

bool loadStage[STAGE_COUNT] = {};
std::mutex mutexStage[STAGE_COUNT];

// ���[�h�g���K�[�n
void SetLoadStage(int stage, bool flag)
{
	std::lock_guard<std::mutex>  lock(mutexStage[stage]);
	loadStage[stage] = flag;
}
bool GetLoadStage(int stage)
{
	std::lock_guard<std::mutex>  lock(mutexStage[stage]);
	return loadStage[stage];
}

#pragma endregion

// �X�e�[�W�̃��[�h
void LoadStage(int stage)
{
	switch (stage)
	{
	case 0:
		modelMngLoad->Load(10, "01_87");		AddRatio(stage);	// 10
		modelMngLoad->Load(11, "01_88");		AddRatio(stage);	// 11
		modelMngLoad->Load(12, "01_89");		AddRatio(stage);	// 12
		//modelMng->Load("01_77");	// 13
		modelMngLoad->Load(14, "01_78");		AddRatio(stage);	// 14
		modelMngLoad->Load(15, "01_79");		AddRatio(stage);	// 15
		modelMngLoad->Load(16, "01_67");		AddRatio(stage);	// 16
		modelMngLoad->Load(17, "01_68");		AddRatio(stage);	// 17
		modelMngLoad->Load(18, "01_69");		AddRatio(stage);	// 18
		modelMngLoad->Load(19, "floor");		AddRatio(stage);	// 19
		modelMngLoad->Load(20, "skydome");		AddRatio(stage);	// 20
		break;											 
														 
	case 1:												 
		modelMngLoad->Load(30, "02_51");		AddRatio(stage);	// 30
		modelMngLoad->Load(31, "02_52");		AddRatio(stage);	// 31
		modelMngLoad->Load(32, "02_53");		AddRatio(stage);	// 32
		//modelMng->Load("01_77");	// 33				 
		modelMngLoad->Load(34, "02_42");		AddRatio(stage);	// 34
		modelMngLoad->Load(35, "02_43");		AddRatio(stage);	// 35
		modelMngLoad->Load(36, "02_31");		AddRatio(stage);	// 36
		modelMngLoad->Load(37, "02_32");		AddRatio(stage);	// 37
		modelMngLoad->Load(38, "02_33");		AddRatio(stage);	// 38
		modelMngLoad->Load(39, "floor");		AddRatio(stage);	// 39
		modelMngLoad->Load(40, "skydome");		AddRatio(stage);	// 40
		break;

	case 2:
		modelMngLoad->Load(50, "03_50");		AddRatio(stage);	// 50
		modelMngLoad->Load(51, "03_51");		AddRatio(stage);	// 51
		modelMngLoad->Load(52, "03_52");		AddRatio(stage);	// 52
		//modelMng->Load("01_77");	// 33				 
		modelMngLoad->Load(54, "03_41");		AddRatio(stage);	// 54
		modelMngLoad->Load(55, "03_42");		AddRatio(stage);	// 55
		modelMngLoad->Load(56, "03_30");		AddRatio(stage);	// 56
		modelMngLoad->Load(57, "03_31");		AddRatio(stage);	// 57
		modelMngLoad->Load(58, "03_32");		AddRatio(stage);	// 58
		modelMngLoad->Load(59, "floor");		AddRatio(stage);	// 59
		modelMngLoad->Load(60, "skydome");		AddRatio(stage);	// 60
		break;

	default:
		break;
	}

	SetLoadStage(stage, true);
}

#pragma endregion

void AsyncLoadStage(int stage)
{
	// �\�ߓǂݍ��ސ����擾
	modelCnt = 0;	// ��U������
	if (!GetLoadDefault())
	{
		modelCnt += LOAD_DEF_MODEL_CNT;
	}
	if (!GetLoadStage(stage))
	{
		modelCnt += LOAD_STAGE_MODEL_CNT;

		// �o�[��i�߂�l�ݒ�
		ratioPiece = 1.0f / modelCnt;
	}

	// ���[�h���ĂȂ��Ȃ炷��
	if (!GetLoadDefault())
	{
		LoadDefault(stage);
	}
	if (!GetLoadStage(stage))
	{
		LoadStage(stage);
	}
}

LoadScene::LoadScene(int stage)
	:	stage(stage)
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
		mapObj = new Fbx();
		mapObj->Initialize();
		switch (stage)
		{
		case 0:
			mapObj->SetModel(modelMngLoad->GetModel(13));
			break;
		case 1:
			mapObj->SetModel(modelMngLoad->GetModel(33));
			break;
		case 2:
			mapObj->SetModel(modelMngLoad->GetModel(53));
			break;
		default:
			break;
		}
		mapObj->SetPosition({ -1130 / 2, 0, -925 - 925 / 2 });
	}

	// �J���������ݒ�
	{
		//camera->SetMouseFlag(false);
	}

	// �񓯊����[�h�J�n
	if (!GetLoadStage(stage))
	{
		th = new std::thread(AsyncLoadStage, stage);
	}
}

void LoadScene::Update()
{
	// �񓯊����[�h��
	if (!GetLoadStage(stage))
	{

	}
	else   // ���[�h�I����
	{
		// SPACE�Ŏ��̃V�[��
		if (input->TriggerKey(DIK_SPACE))
		{
			nextScene = new GameScene(stage);
		}
	}

	// ���[�h�o�[���Z
	float bar = GetRatio(stage) * 800.0f;
	loadBarWhite->SetPosUV({ -GetRatio(stage) + 1.0f, 0 });

	// FBX�X�V
	{
		mapObj->Update();
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
			if (!GetLoadStage(stage))
			{

			}
			else   // ���[�h�I����
			{

			}

			mapObj->Draw(cmdList, true);
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
			if (!GetLoadStage(stage))
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
	if (!GetLoadStage)
	{
		th->join();
	}
}
