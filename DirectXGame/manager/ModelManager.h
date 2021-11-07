#pragma once
#include "FbxModel.h"
#include "FbxLoader.h"
#include <iostream>
#include <vector>

class ModelManager
{
public:
	static ModelManager* GetInstance();
	void Destroy();

	/// <summary>
	/// ���f�������[�h���Ċi�[
	/// </summary>
	/// <param name="modelName">���[�h��</param>
	void Load(const std::string& modelName);

	/// <summary>
	/// ���f���̎擾
	/// </summary>
	/// <param name="modelNum">���f���̕ۑ��ԍ�</param>
	/// <returns>���f��</returns>
	FbxModel* GetModel(int modelNum) { return models[modelNum]; }

private:
	std::vector<FbxModel*> models;
	int modelCnt = 0;

protected:
	static ModelManager* ModelManager::instance;
	ModelManager();
	~ModelManager();
};