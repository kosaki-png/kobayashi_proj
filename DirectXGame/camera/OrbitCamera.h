#pragma once
#include "Camera.h"
#include "Input.h"

/// <summary>
/// �f�o�b�O�p�J����
/// </summary>
class OrbitCamera :
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
	OrbitCamera(int window_width, int window_height);

	// �X�V
	void Update() override;

private:
	// �J���������_�܂ł̋���
	float distance = 20;

	float angleX = 0;	// rad
	float angleY = 0;	// rad

	float theta = 0;
	float phi = 90;

	int WINDOW_WIDTH = 0;
	int WINDOW_HEIGHT = 0;
};

