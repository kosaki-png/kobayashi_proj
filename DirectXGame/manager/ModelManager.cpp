#include "ModelManager.h"

ModelManager* ModelManager::instance = nullptr;

ModelManager::ModelManager()
{
}

ModelManager::~ModelManager()
{
	for (int i = 0; i < modelCnt; i++)
	{
		models.pop_back();
	}
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
	// “Ç‚Ýž‚ñ‚¾ƒ‚ƒfƒ‹‚ð”z—ñ‚É’Ç‰Á
	models.push_back(FbxLoader::GetInstance()->LoadModelFromFile(modelName));
	modelCnt++;
}