#pragma once

#include "SafeDelete.h"
#include "Sprite.h"
#include "DirectXCommon.h"
#include <DirectXMath.h>

class BaseEffect
{
protected: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	/// <summary>
	/// �G�t�F�N�g�C��
	/// </summary>
	void InStart();

	/// <summary>
	/// �G�t�F�N�g�A�E�g
	/// </summary>
	void OutStart();

	// In�����ǂ����̎擾
	bool GetInFlag() { return in; }
	// Out�����ǂ����̎擾
	bool GetOutFlag() { return out; }
	// �G�t�F�N�g���@�\���Ă��邩�̎擾
	bool GetIsEffect() { return isEffect; }

protected:
	bool in = false;	// In�����ʂ��Ă��邩
	bool out = false;	// Out�����ʂ��Ă��邩
	bool isEffect = false;	// �G�t�F�N�g���@�\���Ă��邩

	int effectTimeIn = 0;	// ���ʎ���
	int effectTimeOut = 0;	// ���ʎ���
	int count = 0;			// �X�^�[�g���Ă���̎���

};