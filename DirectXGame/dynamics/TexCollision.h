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
	// enum�̒�`
	enum ArgColor
	{
		Green,    // 0
		Blue,   // 1
		Red,  // 2
		Alpha, // 3
	};

	// �F�����o��
	struct ColorInfo
	{
		unsigned char colors[4];
	};

public: // �ÓI�����o�֐�
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="texWidth">��{�e�N�X�`���̉���</param>
	/// <param name="texHeight">��{�e�N�X�`���̏c��</param>
	/// /// <param name="maxMapX">�z�u�e�N�X�`���̍ő剡</param>
	/// <param name="maxMapY">�z�u�e�N�X�`���̍ő�c</param>
	TexCollision(int texWidth, int texHeight, int maxMapX, int maxMapY);

	~TexCollision();

	/// <summary>
	/// �e�N�X�`���ǂݍ���
	/// </summary>
	/// <param name="mapX">���W�ԍ���</param>
	/// <param name="mapY">���W�ԍ��c</param>
	/// <param name="filename">�摜�t�@�C����</param>
	void LoadTexture(int mapX, int mapY, const wchar_t* filename);

	/// <summary>
	/// �w����W�̃e�N�X�`���F���擾
	/// </summary>
	/// <param name="position">�w����W</param>
	/// <returns>�F���</returns>
	XMFLOAT4 GetPixelColor(XMFLOAT3 position);

	/// <summary>
	/// �w����W���w��F���ǂ���
	/// </summary>
	/// <param name="color">�����蔻������F</param>
	/// <param name="position">���W</param>
	/// <returns>����</returns>
	bool GetHitFlag(ArgColor color, XMFLOAT3 position);

	/// <summary>
	/// �w����W����㉺���E�P�}�X�̐F���疳�F������Έړ��ʂ�����
	/// </summary>
	/// <param name="color">�����蔻������F</param>
	/// <param name="position">���W</param>
	///  <param name="move">�ړ���</param>
	/// <returns>�ύX��ړ���</returns>
	XMFLOAT3 Hit2Color(ArgColor color, XMFLOAT3 position, XMFLOAT3 move);

private:
	ColorInfo* pcolor;

	// ��̉摜�̑傫��
	XMFLOAT2 size;

	// �S�F���
	std::vector<std::vector<ColorInfo>> pixelColors;

	int TEX_WIDTH;
	int TEX_HEIGHT;
};

