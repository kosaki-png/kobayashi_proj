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
	// �F�����o��
	struct ColorInfo
	{
		unsigned char b;
		unsigned char g;
		unsigned char r;
		unsigned char a;
	};

	// �e�N�X�`�����\����
	struct TexInfo
	{
		std::vector<std::vector<ColorInfo>> colors;	// �F���
	};

public: // �ÓI�����o�֐�
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="texWidth">��{�e�N�X�`���̉���</param>
	/// <param name="texHeight">��{�e�N�X�`���̏c��</param>
	/// /// <param name="texWidth">�z�u�e�N�X�`���̍ő剡</param>
	/// <param name="texHeight">�z�u�e�N�X�`���̍ő�c</param>
	TexCollision(int texWidth, int texHeight, int maxMapX, int maxMapY);

	~TexCollision();

	/// <summary>
	/// �e�N�X�`���ǂݍ���
	/// </summary>
	/// <param name="mapX">���W�ԍ���</param>
	/// <param name="mapY">���W�ԍ��c</param>
	/// <param name="filename">�摜�t�@�C����</param>
	/// <returns>����</returns>
	void LoadTexture(int mapX, int mapY, const wchar_t* filename);

	/// <summary>
	/// �w����W�̃e�N�X�`���F���擾
	/// </summary>
	/// <param name="texnum">�e�N�X�`���ԍ�</param>
	/// <param name="position">�w����W</param>
	/// <returns>�F���</returns>
	XMFLOAT4 GetPixelColor(XMFLOAT3 position);

	/// <summary>
	/// �w����W���Ԃ��ǂ���
	/// </summary>
	/// <param name="texnum">�e�N�X�`���ԍ�</param>
	/// <param name="position">�w����W</param>
	/// <returns>����</returns>
	bool GetRedFlag(XMFLOAT3 position);

private:
	ColorInfo* pcolor;

	int texCnt;

	// �e�N�X�`���F���ۑ��ϐ�
	//std::vector<std::vector<ColorInfo>> colors[9];

	XMFLOAT2 size;

	std::vector<std::vector<TexInfo>> textures;

	int TEX_WIDTH;
	int TEX_HEIGHT;
};

