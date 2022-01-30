#include "StageDataStorage.h"

using json = nlohmann::json;

StageDataStorage* StageDataStorage::instance = nullptr;

StageDataStorage* StageDataStorage::GetInstance()
{
	if (!instance)
	{
		instance = new StageDataStorage();
	}
	return instance;
}

void StageDataStorage::LoadJson()
{
	// ファイルを開く
	std::ifstream reading("json/stage_model.json", std::ios::in);

	// ファイル読み込み
	json j;
	reading >> j;

	// デフォルトモデルの名前読み込み
	for (auto x : j["defoultLoad"]["modelNames"])
	{
		defoultModelName.push_back(x.get<std::string>());
	}

	// 総ステージ分データ配列を確保
	stageDatas.resize(j["totalMapNum"].get<int>());

	// 各情報取得
	for (int i = 0; i < stageDatas.size(); i++)
	{
		// ステージ情報へのアクセスパス
		std::string stagePath = "stage" + std::to_string(i);

		// 色情報
		stageDatas[i].color.x = j[stagePath]["color"][0].get<float>();
		stageDatas[i].color.y = j[stagePath]["color"][1].get<float>();
		stageDatas[i].color.z = j[stagePath]["color"][2].get<float>();

		// フォグ色情報
		stageDatas[i].fogColor.x = j[stagePath]["fogColor"][0].get<float>();
		stageDatas[i].fogColor.y = j[stagePath]["fogColor"][1].get<float>();
		stageDatas[i].fogColor.z = j[stagePath]["fogColor"][2].get<float>();
		stageDatas[i].fogColor.w = j[stagePath]["fogColor"][3].get<float>();

		// モデル登録の最初の値
		stageDatas[i].firstNum = j[stagePath]["firstNum"].get<int>();

		// モデルの名前
		for (auto x : j[stagePath]["modelNames"])
		{
			stageDatas[i].modelName.push_back(x.get<std::string>());
		}

		// モデルのズレ
		stageDatas[i].gap.x = j[stagePath]["gap"][0].get<float>();
		stageDatas[i].gap.y = j[stagePath]["gap"][1].get<float>();
		stageDatas[i].gap.z = j[stagePath]["gap"][2].get<float>();
	}
}

StageDataStorage::StageData StageDataStorage::GetStageData(int stage)
{
	if (stageDatas.size() <= stage)
	{
		assert(1);
	}
	return stageDatas[stage];
}

void StageDataStorage::Destroy()
{
	StageDataStorage::~StageDataStorage();
}

StageDataStorage::StageDataStorage()
{
}

StageDataStorage::~StageDataStorage()
{
}
