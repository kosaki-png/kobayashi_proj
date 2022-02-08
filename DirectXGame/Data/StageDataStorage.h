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

public:
	// ���[�h�f�[�^�\����
	struct LoadData
	{
		int firstNum = 0;
		std::vector<std::string> modelName;
	};

	// �X�e�[�W�f�[�^�\����
	struct StageData
	{
		XMFLOAT3 color = { 0,0,0 };				// �X�e�[�W�̐F
		XMFLOAT4 fogColor = { 0,0,0,0 };		// �t�H�O�̐F
		int firstNum = 0;						// ���f���o�^�̎n�߂̔ԍ�
		std::vector<std::string> modelName;		// ���f���̖��O
		XMFLOAT3 gap = { 0,0,0 };				// �X�e�[�W�̃Y��
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

	/// <summary>
	/// �f�t�H���g�œǂݍ��ރ��f���̖��O�擾
	/// </summary>
	/// <returns></returns>
	std::vector<std::string> GetDefoultName() { return defoultModelName; }

	/// <summary>
	/// �Z���N�g���擾
	/// </summary>
	/// <returns></returns>
	LoadData GetDeSelectData() { return selectData; }

private:
	std::vector<std::string> defoultModelName;	// �f�t�H���g�œǂݍ��ރ��f���̖��O
	LoadData selectData;	// �X�e�[�W�Z���N�g�ȂǂŎg�����f��
	std::vector<StageData> stageDatas;	// �}�b�v�f�[�^�z��

private:
	static StageDataStorage* StageDataStorage::instance;
	StageDataStorage();
	~StageDataStorage();
};

