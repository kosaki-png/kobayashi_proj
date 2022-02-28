#pragma once
#include <DirectXMath.h>
#include "SafeDelete.h"

class Button
{
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="position">������W</param>
	/// <param name="scale">�傫��</param>
	Button(XMFLOAT2 position, XMFLOAT2 scale);

	~Button();

	/// <summary>
	/// �w����W���{�^����ɂ��邩
	/// </summary>
	/// <param name="mousePos">�w����W</param>
	/// <returns>�������Ă��邩</returns>
	bool GetHitFlag(XMFLOAT2 position);

private:
	XMFLOAT2 position = { 0,0 };
	XMFLOAT2 scale = { 0,0 };
};

