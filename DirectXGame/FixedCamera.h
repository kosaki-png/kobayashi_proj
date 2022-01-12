#pragma once
#include "Camera.h"
#include "Input.h"

/// <summary>
/// �f�o�b�O�p�J����
/// </summary>
class FixedCamera :
	public Camera
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="window_width">��ʕ�</param>
	/// <param name="window_height">��ʍ���</param>
	/// <param name="input">����</param>
	FixedCamera(int window_width, int window_height);
	~FixedCamera();

	// �X�V
	void Update() override;

private:
	// �J���������_�܂ł̋���
	float distance = 20;
};

