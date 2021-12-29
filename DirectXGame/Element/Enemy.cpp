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

	//DecMoveDir(dir);
}

void Enemy::Update()
{
	switch (dir)
	{
	case Enemy::Up:
		position.z += 0.08f;
		// �ړ��悪�͈͊O�Ȃ�����ύX
		if (texCol->CheckNotBUp(position, LENGTH))
		{
			dir = DecMoveDir(dir);
		}
		break;

	case Enemy::Down:
		position.z -= 0.08f;
		// �ړ��悪�͈͊O�Ȃ�����ύX
		if (texCol->CheckNotBDown(position, LENGTH))
		{
			dir = DecMoveDir(dir);
		}
		break;

	case Enemy::Right:
		position.x += 0.08f;
		// �ړ��悪�͈͊O�Ȃ�����ύX
		if (texCol->CheckNotBRight(position, LENGTH))
		{
			dir = DecMoveDir(dir);
		}
		break;

	case Enemy::Left:
		position.x -= 0.08f;
		// �ړ��悪�͈͊O�Ȃ�����ύX
		if (texCol->CheckNotBLeft(position, LENGTH))
		{
			dir = DecMoveDir(dir);
		}
		break;

	default:
		break;
	}

	enemyObj->SetPosition(position);
	//enemyObj->SetPosition({ 100, 3, 20 });
	enemyObj->SetRotation(rotation);
	enemyObj->SetScale(scale);
	enemyObj->Update();
}

void Enemy::Draw(ID3D12GraphicsCommandList* cmdList)
{
	enemyObj->Draw(cmdList, true);
}

Enemy::Dir Enemy::DecMoveDir(Enemy::Dir dir)
{
	Dir result;

	// �ړ������ɂ���ĎZ�o
	switch (dir)
	{
	case Enemy::Up:
		canRight = texCol->CheckNotBRight(position, LENGTH);
		canLeft = texCol->CheckNotBLeft(position, LENGTH);

		// �ړ������Z�o
		{
			if (!canRight && !canLeft)
			{
				// �����_���ŏo��
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

		// �ړ������Z�o
		{
			if (!canRight && !canLeft)
			{
				// �����_���ŏo��
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

		// �ړ������Z�o
		{
			if (!canUp && !canDown)
			{
				// �����_���ŏo��
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

		// �ړ������Z�o
		{
			if (!canUp && !canDown)
			{
				// �����_���ŏo��
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
