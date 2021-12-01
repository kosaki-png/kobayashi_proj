#include "Player.h"
using namespace DirectX;

Player::Player(int window_width, int window_height)
{
	// ��ʃT�C�Y�ɑ΂��鑊�ΓI�ȃX�P�[���ɒ���
	scaleX = 25.0f / (float)window_width;
	scaleY = 25.0f / (float)window_height;
}

Player::~Player()
{
}

void Player::Initialize(Input* input)
{
	Object::Initialize(input);

	playerObj = new Fbx();
	playerObj->Initialize();
	playerObj->SetModel(modelMng->GetModel(0));

	position = { 0,0,0 };
	cameraTheta = 0;
	cameraTheta = 0;
	cameraPhi = 0;
	playerTheta = 0;
	playerPhi = 0;
}

void Player::Update()
{
	playerObj->SetPosition({ position.x + move.x, position.y + move.y, position.z + move.z });

	// �}�E�X�̓��͂��擾
	Input::MouseMove mouseMove = input->GetMouseMove();

	// �}�E�X�̈ړ��ʕ��J��������]������
	{
		float dy = mouseMove.lX * scaleY;
		float dx = mouseMove.lY * scaleX;

		cameraTheta -= dx;
		cameraPhi += dy;
	}

	// �J�����p�x�ύX(�L�[)
	{
		if (input->PushKey(DIK_UP))
		{
			cameraTheta--;
		}
		if (input->PushKey(DIK_DOWN))
		{
			cameraTheta++;
		}
		if (input->PushKey(DIK_LEFT))
		{
			cameraPhi++;
		}
		if (input->PushKey(DIK_RIGHT))
		{
			cameraPhi--;
		}
	}

	// �����ύX����
	{
		//float tmpTheta = abs(cameraTheta) - abs(playerTheta);
		//float tmpPhi = abs(cameraPhi) - abs(playerPhi);

		//const float MAX_CHANGE_ANGLE = 2.0f;

		//// ���ȏ�Ȃ�Œ�
		//if (tmpTheta > MAX_CHANGE_ANGLE)
		//{
		//	tmpTheta = MAX_CHANGE_ANGLE;
		//}
		//if (tmpTheta < MAX_CHANGE_ANGLE)
		//{
		//	tmpTheta = MAX_CHANGE_ANGLE;
		//}
		//if (tmpPhi > MAX_CHANGE_ANGLE)
		//{
		//	tmpPhi = MAX_CHANGE_ANGLE;
		//}
		//if (tmpPhi < -MAX_CHANGE_ANGLE)
		//{
		//	tmpPhi = -MAX_CHANGE_ANGLE;
		//}

		//if (!speed == 0)
		//{
		//	// �����X�V
		//	if (cameraTheta < playerTheta)
		//	{
		//		playerTheta -= abs(tmpTheta);
		//	}
		//	else
		//	{
		//		playerTheta += abs(tmpTheta);
		//	}
		//	if (cameraPhi < playerPhi)
		//	{
		//		playerPhi -= abs(tmpPhi);
		//	}
		//	else
		//	{
		//		playerPhi += abs(tmpPhi);
		//	}
		//}
	}

	// �O�p�֐��̌v�Z
	//cameraAngleX = -playerPhi * XM_PI / 180;
	//cameraAngleY = -playerTheta * XM_PI / 180;
	cameraAngleX = -cameraPhi * XM_PI / 180;
	cameraAngleY = -cameraTheta * XM_PI / 180;

	float sinX = sinf(cameraAngleX);
	float cosX = cosf(cameraAngleX);
	float sinY = sinf(cameraAngleY);
	float cosY = cosf(cameraAngleY);

	const float CAMERA_DISTANCE = 20;

	move = { 0,0,0 };

	// ���s�ړ�
	{
		position = playerObj->GetPosition();

		// �}�E�X�ł̈ړ��ʑ���
		/*if (input->PushMouseLeft() && speed < 0.9f)
		{
			speed -= 0.01f;
		}
		if (input->PushMouseRight() && speed < -0.5f)
		{
			speed += 0.02f;
		}
		else
		{
			if (speed > 0)
			{
				speed -= 0.005f;
				if (speed < 0)
				{
					speed = 0;
				}
			}
			else if (speed < 0)
			{
				speed += 0.005f;
				if (speed > 0)
				{
					speed = 0;
				}
			}
		}

		move.x = cosX * speed;
		move.z = sinX * speed;*/
		if (input->PushMouseLeft()) speed = -1;
		else if (input->PushMouseRight()) speed = 1;
		else speed = 0;

		move.x = cosX * speed;
		move.z = sinX * speed;

		// WASDQX�ł̈ړ�
		/*if (input->PushKey(DIK_W))
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
		}*/
		if (input->PushKey(DIK_Q)) move.y = 1;
		if (input->PushKey(DIK_X)) move.y = -1;
	}

	//playerObj->SetRotation({ 0, playerPhi - 90, 0 });
	playerObj->SetRotation({ 0, cameraPhi - 90, 0 });

	// �X�V
	playerObj->Update();

	//rePosition = position;
}

void Player::Draw(ID3D12GraphicsCommandList* cmdList)
{
	playerObj->Draw(cmdList, false);
}