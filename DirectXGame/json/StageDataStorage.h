#pragma once
#include <DirectXMath.h>
#include <fstream>
#include <vector>
#include <json.hpp>

class StageDataStorage
{
private: // エイリアス
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	struct StageData
	{
		XMFLOAT3 color = { 0,0,0 };				// ステージの色
		XMFLOAT4 fogColor = { 0,0,0,0 };		// フォグの色
		int firstNum = 0;						// モデル登録の始めの番号
		std::vector<std::string> modelName;		// モデルの名前
		XMFLOAT3 gap = { 0,0,0 };				// ステージのズレ
	};

public:
	static StageDataStorage* GetInstance();
	void Destroy();

	// ステージ情報読み込み
	void LoadJson();

	/// <summary>
	/// ステージ情報取得
	/// </summary>
	/// <param name="stage"></param>
	/// <returns>ステージ情報構造体</returns>
	StageData GetStageData(int stage);

private:
	std::vector<StageData> stageDatas;	// マップデータ配列

private:
	static StageDataStorage* StageDataStorage::instance;
	StageDataStorage();
	~StageDataStorage();
};

