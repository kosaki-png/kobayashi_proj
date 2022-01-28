#pragma once
#include <DirectXMath.h>
#include <fstream>
#include <vector>
#include <json.hpp>

class StageDataStorage
{
private: // �G�C���A�X
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

private:
	struct StageData
	{
		XMFLOAT3 color = { 0,0,0 };				// �X�e�[�W�̐F
		int firstNum = 0;						// ���f���o�^�̎n�߂̔ԍ�
		std::vector<std::string> modelName;		// ���f���̖��O
		XMFLOAT3 gap = { 0,0,0 };				// �X�e�[�W�̃Y��
		std::string texColName = "";			// �����蔻��p�摜�̖��O
		std::string texMapName = "";			// �}�b�v�p�摜�̖��O
	};

public:
	static StageDataStorage* GetInstance();
	void Destroy();

	// �X�e�[�W���ǂݍ���
	void LoadJson();

	/// <summary>
	/// �X�e�[�W���擾
	/// </summary>
	/// <param name="stage"></param>
	/// <returns>�X�e�[�W���\����</returns>
	StageData GetStageData(int stage);

private:
	std::vector<StageData> stageDatas;	// �}�b�v�f�[�^�z��

private:
	static StageDataStorage* StageDataStorage::instance;
	StageDataStorage();
	~StageDataStorage();
};

