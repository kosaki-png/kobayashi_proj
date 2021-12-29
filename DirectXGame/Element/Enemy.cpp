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
	// �����̌����ɉ�����
	switch (dir)
	{
	case Enemy::Up:
		// �ړ��悪�͈͊O�Ȃ�����ύX
		if (texCol->CheckNotBUp(position, LENGTH))
		{
			if (canMove)
			{
				count = 0;
			}

			canMove = false;
			break;
		}

		// ������Ȃ瓮����
		if (canMove)
		{
			position.z += speed;
		}
		break;

	case Enemy::Down:
		// �ړ��悪�͈͊O�Ȃ�����ύX
		if (texCol->CheckNotBDown(position, LENGTH))
		{
			if (canMove)
			{
				count = 0;
			}

			canMove = false;
			break;
		}

		// ������Ȃ瓮����
		if (canMove)
		{
			position.z -= speed;
		}
		break;

	case Enemy::Right:
		// �ړ��悪�͈͊O�Ȃ�����ύX
		if (texCol->CheckNotBRight(position, LENGTH))
		{
			if (canMove)
			{
				count = 0;
			}

			canMove = false;
			break;
		}

		// ������Ȃ瓮����
		if (canMove)
		{
			position.x += speed;
		}
		break;

	case Enemy::Left:
		// �ړ��悪�͈͊O�Ȃ�����ύX
		if (texCol->CheckNotBLeft(position, LENGTH))
		{
			if (canMove)
			{
				count = 0;
			}
			canMove = false;
			break;
		}

		// ������Ȃ瓮����
		if (canMove)
		{
			position.x -= speed;
		}
		break;

	default:
		break;
	}

	// �����ϊ�
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
