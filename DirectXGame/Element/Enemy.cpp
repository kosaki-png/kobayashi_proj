#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize(Input* input, TexCollision* texCol)
{
	Object::Initialize(input, texCol);

	enemyObj = new Fbx();
	enemyObj->Initialize();
	enemyObj->SetModel(modelMng->GetModel(12));
	//enemyObj->SetScale({5, 5, 5});
	position = { 100, 3, 10 };

	count = 1000;
	//DecMoveDir(dir);
}

void Enemy::Update()
{
	// 自分の向きに応じて
	switch (dir)
	{
	case Enemy::Up:
		// 移動先が範囲外なら方向変更
		if (texCol->CheckNotBUp(position, LENGTH))
		{
			if (canMove)
			{
				count = 0;
			}

			canMove = false;
			break;
		}

		// 動けるなら動かす
		if (canMove)
		{
			position.z += speed;
		}
		break;

	case Enemy::Down:
		// 移動先が範囲外なら方向変更
		if (texCol->CheckNotBDown(position, LENGTH))
		{
			if (canMove)
			{
				count = 0;
			}

			canMove = false;
			break;
		}

		// 動けるなら動かす
		if (canMove)
		{
			position.z -= speed;
		}
		break;

	case Enemy::Right:
		// 移動先が範囲外なら方向変更
		if (texCol->CheckNotBRight(position, LENGTH))
		{
			if (canMove)
			{
				count = 0;
			}

			canMove = false;
			break;
		}

		// 動けるなら動かす
		if (canMove)
		{
			position.x += speed;
		}
		break;

	case Enemy::Left:
		// 移動先が範囲外なら方向変更
		if (texCol->CheckNotBLeft(position, LENGTH))
		{
			if (canMove)
			{
				count = 0;
			}
			canMove = false;
			break;
		}

		// 動けるなら動かす
		if (canMove)
		{
			position.x -= speed;
		}
		break;

	default:
		break;
	}

	// 方向変換
	{
		if (count == 0)
		{
			
		}
		if (count == CHANGEDIR_STOP)
		{

		}
		if (count == CHANGEDIR + CHANGEDIR_STOP)
		{
			dir = DecMoveDir(dir);
			canMove = true;
		}
	}

	enemyObj->SetPosition(position);
	//enemyObj->SetPosition({ 100, 3, 20 });
	enemyObj->SetRotation(rotation);
	enemyObj->SetScale(scale);
	enemyObj->Update();

	count++;
}

void Enemy::Draw(ID3D12GraphicsCommandList* cmdList)
{
	enemyObj->Draw(cmdList, true);
}

Enemy::Dir Enemy::DecMoveDir(Enemy::Dir dir)
{
	Dir result;

	// 移動方向によって算出
	switch (dir)
	{
	case Enemy::Up:
		canRight = texCol->CheckNotBRight(position, LENGTH);
		canLeft = texCol->CheckNotBLeft(position, LENGTH);

		// 移動方向算出
		{
			if (!canRight && !canLeft)
			{
				// ランダムで出す
				if (std::rand() % 2 == 0)
				{
					result = Right;
				}
				else
				{
					result = Left;
				}
			}
			else if (!canRight && canLeft)
			{
				result = Right;
			}
			else if (canRight && !canLeft)
			{
				result = Left;
			}
			else
			{
				result = Down;
			}
		}

		break;
	case Enemy::Down:
		canRight = texCol->CheckNotBRight(position, LENGTH);
		canLeft = texCol->CheckNotBLeft(position, LENGTH);

		// 移動方向算出
		{
			if (!canRight && !canLeft)
			{
				// ランダムで出す
				if (std::rand() % 2 == 0)
				{
					result = Right;
				}
				else
				{
					result = Left;
				}
			}
			else if (!canRight && canLeft)
			{
				result = Right;
			}
			else if (canRight && !canLeft)
			{
				result = Left;
			}
			else
			{
				result = Up;
			}
		}

		break;
	case Enemy::Right:
		canUp = texCol->CheckNotBUp(position, LENGTH);
		canDown = texCol->CheckNotBDown(position, LENGTH);

		// 移動方向算出
		{
			if (!canUp && !canDown)
			{
				// ランダムで出す
				if (std::rand() % 2 == 0)
				{
					result = Up;
				}
				else
				{
					result = Down;
				}
			}
			else if (!canUp && canDown)
			{
				result = Up;
			}
			else if (canUp && !canDown)
			{
				result = Down;
			}
			else
			{
				result = Left;
			}
		}

		break;
	case Enemy::Left:
		canUp = texCol->CheckNotBUp(position, LENGTH);
		canDown = texCol->CheckNotBDown(position, LENGTH);

		// 移動方向算出
		{
			if (!canUp && !canDown)
			{
				// ランダムで出す
				if (std::rand() % 2 == 0)
				{
					result = Up;
				}
				else
				{
					result = Down;
				}
			}
			else if (!canUp && canDown)
			{
				result = Up;
			}
			else if (canUp && !canDown)
			{
				result = Down;
			}
			else
			{
				result = Right;
			}
		}

		break;
	default:
		break;
	}

	switch (result)
	{
	case Enemy::Up:
		rotation = { 0,0,0 };
		break;
	case Enemy::Down:
		rotation = { 0,180,0 };
		break;
	case Enemy::Right:
		rotation = { 0,90,0 };
		break;
	case Enemy::Left:
		rotation = { 0,-90,0 };
		break;
	default:
		break;
	}

	return result;
}
