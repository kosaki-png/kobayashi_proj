#pragma once
#include "Camera.h"
#include "Input.h"

/// <summary>
/// �f�o�b�O�p�J����
/// </summary>
class MainCamera :
	public Camera
{
private:
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="window_width">��ʕ�</param>
	/// <param name="window_height">��ʍ���</param>
	/// <param name="input">����</param>
	MainCamera(int window_width, int window_height, Input* input);

	// �J�����̕��s�ړ�
	void SetCameraPos(XMFLOAT3 position);

	// �X�V
	void Update() override;

	void SetDistance(float distance) {
		this->distance = distance; viewDirty = true;
	}

	//// �J�����̈ړ�
	//void CameraMove(XMFLOAT3 moveVel) { this->moveVel = moveVel; dirty = true; }

	// thita,phi�̎擾
	XMFLOAT2 GetAngle() { return { angleX, angleY }; }

	// ���x�ύX
	void SetSence(float sence);
	float GetSence() { return sence; }

	// �}�E�X�œ������t���O�ύX
	void SetMouseFlag(bool mouse) { this->mouse = mouse; }

private:
	// ���̓N���X�̃|�C���^
	Input* input;
	// �J���������_�܂ł̋���
	float distance = 20;
	// �X�P�[�����O
	float scaleX = 1.0f;
	float scaleY = 1.0f;
	// ��]�s��
	XMMATRIX matRot = DirectX::XMMatrixIdentity();

	bool dirty = false;

	float angleX = 0;	// rad
	float angleY = 0;	// rad

	XMFLOAT3 moveVel = { 0,0,0 };

	float theta = 0;
	float phi = 90;

	XMFLOAT3 moveVec = { 0,0,0 };

	float sence = 1.0f;

	int WINDOW_WIDTH = 0;
	int WINDOW_HEIGHT = 0;

	bool mouse = true;
};

