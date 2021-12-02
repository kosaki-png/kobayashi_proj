#include "MainCamera.h"
#include <cassert>

using namespace DirectX;

MainCamera::MainCamera(int window_width, int window_height, Input* input)
	: Camera(window_width, window_height)
{
	assert(input);
	this->input = input;

	WINDOW_WIDTH = window_width;
	WINDOW_HEIGHT = window_height;

	// ��ʃT�C�Y�ɑ΂��鑊�ΓI�ȃX�P�[���ɒ���
	scaleX = sence * 25.0f / (float)WINDOW_WIDTH;
	scaleY = sence * 25.0f / (float)WINDOW_HEIGHT;
}

void MainCamera::SetCameraPos(DirectX::XMFLOAT3 position)
{
	XMVECTOR move = { position.x, position.y, position.z, 0 };
	move = XMVector3Transform(move, matRot);

	MoveVector(move);
}

void MainCamera::Update()
{
	// �}�E�X�̓��͂��擾
	Input::MouseMove mouseMove = input->GetMouseMove();

	// �}�E�X�̈ړ��ʕ��J��������]������
	{
		float dy = mouseMove.lX * scaleY;
		float dx = mouseMove.lY * scaleX;

		theta -= dx;
		phi += dy;
	}

	// �J�����p�x�ύX(�L�[)
	{
		if (input->PushKey(DIK_UP))
		{
			theta--;
		}
		if (input->PushKey(DIK_DOWN))
		{
			theta++;
		}
		if (input->PushKey(DIK_LEFT))
		{
			phi++;
		}
		if (input->PushKey(DIK_RIGHT))
		{
			phi--;
		}
	}

	// �O�p�֐��̌v�Z
	angleX = -phi * XM_PI / 180;
	angleY = -theta * XM_PI / 180;

	float sinX = sinf(angleX);
	float cosX = cosf(angleX);
	float sinY = sinf(angleY);
	float cosY = cosf(angleY);

	const float CAMERA_DISTANCE = 10;
	XMFLOAT3 target = GetTarget();

	SetEye({ cosX * cosY * CAMERA_DISTANCE + target.x,
			 sinY *		   CAMERA_DISTANCE + target.y,
			 sinX * cosY * CAMERA_DISTANCE + target.z });

	Camera::Update();
}

void MainCamera::SetSence(float sence)
{
	this->sence = sence;

	// ��ʃT�C�Y�ɑ΂��鑊�ΓI�ȃX�P�[���ɒ���
	scaleX = sence * 25.0f / (float)WINDOW_WIDTH;
	scaleY = sence * 25.0f / (float)WINDOW_HEIGHT;
}
