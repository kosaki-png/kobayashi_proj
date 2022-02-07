#include "Player.h"

using namespace DirectX;
using ArgColor = TexCollision::ArgColor;

Player::Player(int window_width, int window_height) : 
	WINDOW_WIDTH(window_width), WINDOW_HEIGHT(window_height)
{
	// ��ʃT�C�Y�ɑ΂��鑊�ΓI�ȃX�P�[���ɒ���
	scaleX = 25.0f / (float)WINDOW_WIDTH;
	scaleY = 25.0f / (float)WINDOW_HEIGHT;
}

Player::~Player()
{
	delete playerObj;
	delete dangerSpr;
	delete arrowObj;
}

void Player::Initialize(Input* input, TexCollision* texCol)
{
	Sprite::LoadTexture(10, L"Resources/texture/danger.png");
	dangerSpr = Sprite::Create(10, { 0,0 });

	Object::Initialize(input, texCol);

	playerObj = new Fbx();
	playerObj->Initialize();
	playerObj->SetModel(modelMng->GetModel(0));
	playerObj->SetScale({1.5f, 1.5f, 1.5f});

	arrowObj = new Fbx();
	arrowObj->Initialize({ 0,1,0 });
	arrowObj->SetModel(modelMng->GetModel(6));

	Placement(TexCollision::ArgColor::Green);
}

void Player::Update()
{
	playerObj->SetPosition({ position.x + move.x, position.y + move.y, position.z + move.z });
	arrowObj->SetPosition({ position.x + move.x, position.y + move.y, position.z + move.z });

	// �}�E�X�̓��͂��擾
	Input::MouseMove mouseMove = input->GetMouseMove();

	// �}�E�X�̈ړ��ʕ���]������
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

	// �O�p�֐��̌v�Z
	cameraAngleX = -cameraPhi * XM_PI / 180;
	cameraAngleY = -cameraTheta * XM_PI / 180;

	rotation = { 0, cameraPhi - 90, 0 };

	float sinX = sinf(cameraAngleX);
	float cosX = cosf(cameraAngleX);
	float sinY = sinf(cameraAngleY);
	float cosY = cosf(cameraAngleY);

	const float CAMERA_DISTANCE = 20;

	move = { 0,0,0 };

	// ���s�ړ�
	{
		position = playerObj->GetPosition();

		// shift�Ń_�b�V��
		if (input->PushKey(DIK_LSHIFT))
		{
			speed = 1;
		}
		else
		{
			speed = 0.5f;
		}

		// WASDQX�ł̈ړ�
		if (input->PushKey(DIK_W))
		{
			move.x += -cosX * speed;
			move.z += -sinX * speed;
		}
		if (input->PushKey(DIK_S))
		{
			move.x += cosX * speed;
			move.z += sinX * speed;
		}
		if (input->PushKey(DIK_A))
		{
			move.x += sinX * speed;
			move.z += -cosX * speed;
		}
		if (input->PushKey(DIK_D))
		{
			move.x += -sinX * speed;
			move.z += cosX * speed;
		}
		if (input->PushKey(DIK_Q)) move.y = 1;
		if (input->PushKey(DIK_X)) move.y = -1;
	}

	if (danger)
	{
		if (dangerAlpha < 1)
		{
			dangerAlpha += 0.02f;
		}
	}
	else
	{
		if (dangerAlpha > 0)
		{
			dangerAlpha -= 0.02f;
		}
	}

	dangerSpr->SetAlpha(dangerAlpha);

	// �v���C���[�̌�����ݒ�
	playerObj->SetRotation(rotation);

	// �ړ��ʂɓ����蔻��𔽉f
	move = texCol->Hit2Color(ArgColor::Red, position, move);

	arrowRot.y = crystalRad * 180.0f / 3.14f + 180.0f;
	arrowObj->SetRotation(arrowRot);

	// �X�V
	playerObj->Update();
	arrowObj->Update();
}

void Player::Draw(ID3D12GraphicsCommandList* cmdList)
{
	playerObj->Draw(cmdList);
	arrowObj->Draw(cmdList);
}

void Player::SpriteDraw()
{
	dangerSpr->Draw();
}

void Player::SetSence(float sence)
{
	this->sence = sence;

	// ��ʃT�C�Y�ɑ΂��鑊�ΓI�ȃX�P�[���ɒ���
	scaleX = sence * 25.0f / (float)WINDOW_WIDTH;
	scaleY = sence * 25.0f / (float)WINDOW_HEIGHT;
}
