#include "Player.h"
using namespace DirectX;

Player::Player(int window_width, int window_height)
{
	// 画面サイズに対する相対的なスケールに調整
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

	// マウスの入力を取得
	Input::MouseMove mouseMove = input->GetMouseMove();

	// マウスの移動量分カメラを回転させる
	{
		float dy = mouseMove.lX * scaleY;
		float dx = mouseMove.lY * scaleX;

		theta -= dx;
		phi += dy;
	}

	// カメラ角度変更(キー)
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

	// 三角関数の計算
	angleX = -phi * XM_PI / 180;
	angleY = -theta * XM_PI / 180;

	float sinX = sinf(angleX);
	float cosX = cosf(angleX);
	float sinY = sinf(angleY);
	float cosY = cosf(angleY);

	const float CAMERA_DISTANCE = 20;

	XMFLOAT3 move = { 0,0,0 };

	// 平行移動
	{
		position = playerObj->GetPosition();

		// マウスでの移動
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

		// WASDQXでの移動
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

	// 更新
	playerObj->Update();

	rePosition = position;
}

void Player::Draw(ID3D12GraphicsCommandList* cmdList)
{
	playerObj->Draw(cmdList, false);
}