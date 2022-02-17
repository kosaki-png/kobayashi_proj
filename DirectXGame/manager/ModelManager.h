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
	/// モデルをロードして格納
	/// </summary>
	/// <param name="modelName">ロード名</param>
	void Load(int modelNum, const std::string& modelName);

	/// <summary>
	/// モデルの取得
	/// </summary>
	/// <param name="modelNum">モデルの保存番号</param>
	/// <returns>モデル</returns>
	FbxModel* GetModel(int modelNum) { return models[modelNum]; }

	/// <summary>
	/// 指定番号のモデルを削除
	/// </summary>
	/// <param name="modelNum"></param>
	void SpecifyRelease(int modelNum);

private:
	std::vector<FbxModel*> models;
	int modelCnt = 0;

protected:
	static ModelManager* ModelManager::instance;
	ModelManager();
	~ModelManager();
};