#include "IntervalScene.h"

#include <cassert>
#include <sstream>
#include <iomanip>
#include <thread>

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
	// �񓯊����[�h�J�n
	if (!isLoaded)
	{
		th = new std::thread(AsyncLoad);
	}
}

void IntervalScene::Update()
{
	// �񓯊����[�h��
	if (GetLockFlag())
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
}

void IntervalScene::Draw()
{
}

void IntervalScene::Finalize()
{
	if (!isLoaded)
	{
		th->join();
	}
}
