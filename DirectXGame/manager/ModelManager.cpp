#include "ModelManager.h"

ModelManager* ModelManager::instance = nullptr;

ModelManager::ModelManager()
{
}

ModelManager::~ModelManager()
{
	models.clear();
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
	// 読み込んだモデルを配列に追加
	models.push_back(FbxLoader::GetInstance()->LoadModelFromFile(modelName));
	modelCnt++;
}