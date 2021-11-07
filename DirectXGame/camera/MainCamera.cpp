#include "MainCamera.h"
#include <cassert>

using namespace DirectX;

MainCamera::MainCamera(int window_width, int window_height, Input* input)
	: Camera(window_width, window_height)
{
	assert(input);

	this->input = input;
	// ��ʃT�C�Y�ɑ΂��鑊�ΓI�ȃX�P�[���ɒ���
	scaleX = 25.0f / (float)window_width;
	scaleY = 25.0f / (float)window_height;
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

	const float CAMERA_DISTANCE = 20;
	XMFLOAT3 target = GetTarget();

	move = { 0,0,0 };

	// ���s�ړ�
	{
		if (input->PushKey(DIK_W)) 
		{
			move.x += -cosX;
			move.z += -sinX;
		}
		if (input->PushKey(DIK_S)) 
		{
			move.x += cosX;
			move.z += sinX;
		}
		if (input->PushKey(DIK_A)) 
		{
			move.x += sinX;
			move.z += -cosX;
		}
		if (input->PushKey(DIK_D)) 
		{
			move.x += -sinX;
			move.z += cosX;
		}
		if (input->PushKey(DIK_Q)) move.y += 1;
		if (input->PushKey(DIK_X)) move.y += -1;

		SetTarget({ target.x + move.x,  target.y + move.y,  target.z + move.z });
		moveVec.x += move.x;
		moveVec.y += move.y;
		moveVec.z += move.z;
	}

	target = GetTarget();

	SetEye({ cosX * cosY * CAMERA_DISTANCE + target.x,
			 sinY * CAMERA_DISTANCE + target.y,
			 sinX * cosY * CAMERA_DISTANCE + target.z });

	Camera::Update();
}