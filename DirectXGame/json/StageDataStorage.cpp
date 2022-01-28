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
	// �t�@�C�����J��
	std::ifstream reading("json/test.json", std::ios::in);

	// �t�@�C���ǂݍ���
	json j;
	reading >> j;

	// ���X�e�[�W���f�[�^�z����m��
	stageDatas.resize(j["totalMapNum"].get<int>());

	// �e���擾
	for (int i = 0; i < stageDatas.size(); i++)
	{
		// �X�e�[�W���ւ̃A�N�Z�X�p�X
		std::string stagePath = "stage" + std::to_string(i);

		// �F���
		stageDatas[i].color.x = j[stagePath]["color"][0].get<float>();
		stageDatas[i].color.y = j[stagePath]["color"][1].get<float>();
		stageDatas[i].color.z = j[stagePath]["color"][2].get<float>();

		// ���f���o�^�̍ŏ��̒l
		stageDatas[i].firstNum = j[stagePath]["firstNum"].get<int>();

		// ���f���̖��O
		for (auto x : j[stagePath]["modelNames"])
		{
			stageDatas[i].modelName.push_back(x.get<std::string>());
		}

		// ���f���̃Y��
		stageDatas[i].gap.x = j[stagePath]["gap"][0].get<float>();
		stageDatas[i].gap.y = j[stagePath]["gap"][1].get<float>();
		stageDatas[i].gap.z = j[stagePath]["gap"][2].get<float>();

		// �����蔻��p�摜�̖��O
		stageDatas[i].texColName = j[stagePath]["texColName"].get<std::string>();

		// �}�b�v�p�摜�̖��O
		stageDatas[i].texMapName = j[stagePath]["texMapName"].get<std::string>();
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
