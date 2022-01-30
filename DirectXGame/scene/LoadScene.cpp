#include "LoadScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>

using namespace DirectX;

// ���f���Ǘ��N���X�̃C���X�^���X�擾
ModelManager* modelMngLoad = ModelManager::GetInstance();

const int STAGE_COUNT = 4;		// �X�e�[�W�̐�

const int LOAD_DEF_MODEL_CNT = 7;		// �f�t�H���g�Ń��[�h���郂�f���̐�
const int LOAD_STAGE_MODEL_CNT = 11;	// �X�e�[�W			�V

// ���[�h�o�[����
float loadRatio[STAGE_COUNT] = { 0, 0, 0 };
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
	modelMngLoad->Load(3, "crystal");			AddRatio(stage);	// 3
	modelMngLoad->Load(4, "crystalCircle");		AddRatio(stage);	// 4
	modelMngLoad->Load(5, "Particle_Cube");		AddRatio(stage);	// 5
	modelMngLoad->Load(6, "Arrow");				AddRatio(stage);	// 6

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
	// �w�肵���X�e�[�W���̎擾
	StageDataStorage::StageData stageData = StageDataStorage::GetInstance()->GetStageData(stage);

	// �X�e�[�W��񂩂烂�f�������[�h
	for (int i = 0; i < stageData.modelName.size(); i++)
	{
		modelMngLoad->Load(stageData.firstNum + i, stageData.modelName[i]);
		AddRatio(stage);
	}

	SetLoadStage(stage, true);
}

#pragma endregion

void AsyncLoadStage(int stage)
{
	// �\�ߓǂݍ��ސ����擾
	int modelCnt = 0;
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
	delete mapObj;
	delete loading;
	delete loaded;
	delete loadBar;
	delete loadBarWhite;
}

void LoadScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio)
{
	// nullptr�`�F�b�N
	BaseScene::Initialize(dxCommon, input, audio);

	// �ėp�I������
	{
		// �J��������
		camera = new OrbitCamera(WinApp::window_width, WinApp::window_height);

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
			// ���[�h�o�[�Ȃǂ̐F���Z�b�g
			XMFLOAT4 color = { stageData->GetStageData(stage).color.x,
							   stageData->GetStageData(stage).color.y,
							   stageData->GetStageData(stage).color.z, 1 };
			loading->SetColor(color);
			loaded->SetColor(color);
			loadBar->SetColor(color);
		}
	}

	// FBX�I�u�W�F�N�g�����ݒ�
	{
		mapObj = new Fbx();
		mapObj->Initialize();
		// �}�b�v���f���Z�b�g
		mapObj->SetModel(modelMngLoad->GetModel(stage * 20 + 13));
		mapObj->SetPosition({ -1130 / 2, 0, -925 - 925 / 2 });
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
		// �}�b�v�`��
		mapObj->Draw(cmdList, true);

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
}

void LoadScene::Finalize()
{
	if (!GetLoadStage(stage))
	{
		th->join();
	}
}
