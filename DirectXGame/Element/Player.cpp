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
	playerObj->SetModel(modelMng->GetModel(1));

	position = { 0,0,0 };
	theta = 0;
	phi = 0;
}

void Player::Update()
{
	playerObj->SetPosition(rePosition);

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

	XMFLOAT3 move = { 0,0,0 };

	// ���s�ړ�
	{
		position = playerObj->GetPosition();

		// �}�E�X�ł̈ړ�
		if (input->PushMouseLeft())
		{
			move.x += -cosX;
			move.z += -sinX;
		}
		if (input->PushMouseRight())
		{
			move.x += cosX;
			move.z += sinX;
		}

		// WASDQX�ł̈ړ�
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

		position.x += move.x;
		position.y += move.y;
		position.z += move.z;
	}

	// �X�V
	playerObj->Update();

	rePosition = position;
}

void Player::Draw(ID3D12GraphicsCommandList* cmdList)
{
	playerObj->Draw(cmdList, false);
}