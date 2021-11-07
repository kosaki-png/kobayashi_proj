#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <SafeDelete.h>
#include <vector>

/// <summary>
/// �X�v���C�g
/// </summary>
class TexCollision
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: // �T�u�N���X
	/// <summary>
	/// ���_�f�[�^�\����
	/// </summary>
	struct VertexPosUv
	{
		XMFLOAT3 pos; // xyz���W
		XMFLOAT2 uv;  // uv���W
	};

	/// <summary>
	/// �萔�o�b�t�@�p�f�[�^�\����
	/// </summary>
	struct ConstBufferData
	{
		XMFLOAT4 color;	// �F (RGBA)
		XMMATRIX mat;	// �R�c�ϊ��s��
	};

	// �F�����o��
	struct ColorInfo
	{
		unsigned char b;
		unsigned char g;
		unsigned char r;
		unsigned char a;
	};

public: // �ÓI�����o�֐�
	TexCollision();
	~TexCollision();

	/// <summary>
	/// �e�N�X�`���ǂݍ���
	/// </summary>
	/// <param name="texnumber">�e�N�X�`���ԍ�</param>
	/// <param name="filename">�摜�t�@�C����</param>
	/// <returns>����</returns>
	void LoadTexture(int texnumber, const wchar_t* filename);

	/// <summary>
	/// �w����W�̃e�N�X�`���F���擾
	/// </summary>
	/// <param name="texnum">�e�N�X�`���ԍ�</param>
	/// <param name="position">�w����W</param>
	/// <returns>�F���</returns>
	XMFLOAT4 GetPixelColor(int texNum, XMFLOAT2 position);

	/// <summary>
	/// �w����W���Ԃ��ǂ���
	/// </summary>
	/// <param name="texnum">�e�N�X�`���ԍ�</param>
	/// <param name="position">�w����W</param>
	/// <returns>����</returns>
	bool GetRedFlag(int texNum, XMFLOAT2 position);

private:
	ColorInfo* pcolors[9];

	int texCnt;

	// �e�N�X�`���F���ۑ��ϐ�
	std::vector<std::vector<ColorInfo>> colors[9];

	XMFLOAT2 size;
};

