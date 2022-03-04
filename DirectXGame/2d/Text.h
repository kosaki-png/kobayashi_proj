#pragma once

#include "Sprite.h"
#include "SpriteData.h"
#include <Windows.h>
#include <string>
#include <memory>
#include <array>
#include <DirectXMath.h>

class Text
{
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;

public:
	static const int maxCharCount = 32;	// �ő啶����
	static const int fontWidth = 100;			// �t�H���g�摜��1�������̉���
	static const int fontHeight = 150;		// �t�H���g�摜��1�������̏c��

public:
	static Text* GetInstance();

	void Initialize();

	/// <summary>
	/// ��������`��
	/// </summary>
	/// <param name="number">�\�����鐔���i�ő�X�X�j</param>
	/// <param name="position">������W</param>
	/// <param name="scale">�����̑傫��</param>
	void PrintNumber(int number, XMFLOAT2 position, float scale = 1);

	/// <summary>
	/// ���ԕ`��
	/// </summary>
	/// <param name="minutes">���i�ő�X�X�j</param>
	/// <param name="seconds">�b�i�ő�X�X�j</param>
	/// <param name="position">������W</param>
	/// <param name="scale">�傫��</param>
	void PrintTime(int min, int sec, XMFLOAT2 position, float scale = 1);

	/// <summary>
	/// �X�R�A�`��
	/// </summary>
	/// <param name="now">���̃X�R�A</param>
	/// <param name="all">�W�߂鑍��</param>
	/// <param name="position">������W</param>
	/// <param name="scale">�傫��</param>
	void PrintScore(int now, int all, XMFLOAT2 position, float scale = 1);

	void DrawAll();

	void Destroy();

private:
	Text();
	~Text();

	static Text* instance;

	// �����\���p�̃X�v���C�g
	std::array<std::unique_ptr<Sprite>, maxCharCount> sprite;

	int indexCnt = 0;

};

