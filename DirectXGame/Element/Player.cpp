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

	// マウスの入力を取得
	Input::MouseMove mouseMove = input->GetMouseMove();

	// マウスの移動量分カメラを回転させる
	{
		float dy = mouseMove.lX * scaleY;
		float dx = mouseMove.lY * scaleX;

		cameraTheta -= dx;
		cameraPhi += dy;
	}

	// カメラ角度変更(キー)
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

	// 向き変更制限
	{
		//float tmpTheta = abs(cameraTheta) - abs(playerTheta);
		//float tmpPhi = abs(cameraPhi) - abs(playerPhi);

		//const float MAX_CHANGE_ANGLE = 2.0f;

		//// 一定以上なら固定
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
		//	// 向き更新
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

	// 三角関数の計算
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

	// 平行移動
	{
		position = playerObj->GetPosition();

		// マウスでの移動量増加
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

		// WASDQXでの移動
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

	// 更新
	playerObj->Update();

	//rePosition = position;
}

void Player::Draw(ID3D12GraphicsCommandList* cmdList)
{
	playerObj->Draw(cmdList, false);
}