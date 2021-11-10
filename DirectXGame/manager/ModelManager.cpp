#include "ModelManager.h"

ModelManager* ModelManager::instance = nullptr;

ModelManager::ModelManager()
{
}

ModelManager::~ModelManager()
{
	delete[] &models;
}

ModelManager* ModelManager::GetInstance()
{
	if (!instance)
	{
		instance = new ModelManager();
	}
	return instance;
}

void ModelManager::Destroy()
{
	ModelManager::~ModelManager();
}

void ModelManager::Load(const std::string& modelName)
{
	// �ǂݍ��񂾃��f����z��ɒǉ�
	models.push_back(FbxLoader::GetInstance()->LoadModelFromFile(modelName));
	modelCnt++;
}