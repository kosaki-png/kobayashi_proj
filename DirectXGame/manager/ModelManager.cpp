#include "ModelManager.h"

ModelManager* ModelManager::instance = nullptr;

ModelManager::ModelManager()
{
}

ModelManager::~ModelManager()
{
	for (auto x : models)
	{
		delete x;
	}
	delete instance;
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

void ModelManager::Load(int modelNum, const std::string& modelName)
{
	// �T�C�Y������Ȃ��Ƃ��͒ǉ�����
	if (modelNum + 1 > models.size())
	{
		models.resize(modelNum + 1);
	}

	// �ǂݍ��񂾃��f����z��ɒǉ�
	models[modelNum] = FbxLoader::GetInstance()->LoadModelFromFile(modelName);
}