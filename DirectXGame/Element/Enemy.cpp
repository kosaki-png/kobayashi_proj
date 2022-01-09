#include "Enemy.h"
using ArgColor = TexCollision::ArgColor;
using Dir = TexCollision::Dir;

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
	delete enemyObj;
	delete circleObj;
}

void Enemy::Initialize(Input* input, TexCollision* texCol)
{
	Object::Initialize(input, texCol);

	enemyObj = new Fbx();
	enemyObj->Initialize();
	enemyObj->SetModel(modelMng->GetModel(1));
	//enemyObj->SetScale({5, 5, 5});

	circleObj = new Fbx();
	circleObj->Initialize();
	circleObj->SetModel(modelMng->GetModel(2));

	stopCnt = 1000;
	Placement();
}

void Enemy::Update()
{
	// �����̌����ɉ����Đi��
	switch (dir)
	{
	case Dir::Up:
		// �ړ��悪�͈͊O�Ȃ�����ύX
		if (texCol->CheckNot(ArgColor::Blue, Dir::Up, position, LENGTH))
		{
			if (canMove)
			{
				stopCnt = 0;
			}

			canMove = false;
			break;
		}

		// ������Ȃ瓮����
		if (canMove)
		{
			position.z += speedLow;
		}
		break;

	case Dir::Down:
		// �ړ��悪�͈͊O�Ȃ�����ύX
		if (texCol->CheckNot(ArgColor::Blue, Dir::Down, position, LENGTH))
		{
			if (canMove)
			{
				stopCnt = 0;
			}

			canMove = false;
			break;
		}

		// ������Ȃ瓮����
		if (canMove)
		{
			position.z -= speedLow;
		}
		break;

	case Dir::Right:
		// �ړ��悪�͈͊O�Ȃ�����ύX
		if (texCol->CheckNot(ArgColor::Blue, Dir::Right, position, LENGTH))
		{
			if (canMove)
			{
				stopCnt = 0;
			}

			canMove = false;
			break;
		}

		// ������Ȃ瓮����
		if (canMove)
		{
			position.x += speedLow;
		}
		break;

	case Dir::Left:
		// �ړ��悪�͈͊O�Ȃ�����ύX
		if (texCol->CheckNot(ArgColor::Blue, Dir::Left, position, LENGTH))
		{
			if (canMove)
			{
				stopCnt = 0;
			}
			canMove = false;
			break;
		}

		// ������Ȃ瓮����
		if (canMove)
		{
			position.x -= speedLow;
		}
		break;

	default:
		break;
	}

	// �����ϊ�
	{
		if (stopCnt == 0)
		{
			
		}
		if (stopCnt == CHANGEDIR_STOP)
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

	circleObj->SetPosition(position);
	circleObj->SetRotation(rotation);
	circleObj->Update();

	stopCnt++;
}

void Enemy::Draw(ID3D12GraphicsCommandList* cmdList)
{
	enemyObj->Draw(cmdList, true);
	circleObj->Draw(cmdList, false);
}

void Enemy::SpriteDraw()
{
}

void Enemy::Placement()
{
	while (true)
	{
		// ���W�Z�b�g
		position = { (float)(std::rand() % 3390), 3, (float)(std::rand() % 2775) };
		// �������Ȃ�z�u����
		if (texCol->GetHitFlag(ArgColor::Blue, position))
		{
			break;
		}
	}
}

Dir Enemy::DecMoveDir(Dir dir)
{
	Dir result;

	bool canRight, canLeft, canUp, canDown;

	// �ړ������ɂ���ĎZ�o
	switch (dir)
	{
	case Dir::Up:
		canRight = texCol->CheckNot(ArgColor::Blue, Dir::Right, position, LENGTH);
		canLeft = texCol->CheckNot(ArgColor::Blue, Dir::Left, position, LENGTH);

		// �ړ������Z�o
		{
			if (!canRight && !canLeft)
			{
				// �����_���ŏo��
				if (std::rand() % 2 == 0)
				{
					result = Dir::Right;
				}
				else
				{
					result = Dir::Left;
				}
			}
			else if (!canRight && canLeft)
			{
				result = Dir::Right;
			}
			else if (canRight && !canLeft)
			{
				result = Dir::Left;
			}
			else
			{
				result = Dir::Down;
			}
		}

		break;
	case Dir::Down:
		canRight = texCol->CheckNot(ArgColor::Blue, Dir::Right, position, LENGTH);
		canLeft = texCol->CheckNot(ArgColor::Blue, Dir::Left, position, LENGTH);

		// �ړ������Z�o
		{
			if (!canRight && !canLeft)
			{
				// �����_���ŏo��
				if (std::rand() % 2 == 0)
				{
					result = Dir::Right;
				}
				else
				{
					result = Dir::Left;
				}
			}
			else if (!canRight && canLeft)
			{
				result = Dir::Right;
			}
			else if (canRight && !canLeft)
			{
				result = Dir::Left;
			}
			else
			{
				result = Dir::Up;
			}
		}

		break;
	case Dir::Right:
		canUp = texCol->CheckNot(ArgColor::Blue, Dir::Up, position, LENGTH);
		canDown = texCol->CheckNot(ArgColor::Blue, Dir::Down, position, LENGTH);

		// �ړ������Z�o
		{
			if (!canUp && !canDown)
			{
				// �����_���ŏo��
				if (std::rand() % 2 == 0)
				{
					result = Dir::Up;
				}
				else
				{
					result = Dir::Down;
				}
			}
			else if (!canUp && canDown)
			{
				result = Dir::Up;
			}
			else if (canUp && !canDown)
			{
				result = Dir::Down;
			}
			else
			{
				result = Dir::Left;
			}
		}

		break;
	case Dir::Left:
		canUp = texCol->CheckNot(ArgColor::Blue, Dir::Up, position, LENGTH);
		canDown = texCol->CheckNot(ArgColor::Blue, Dir::Down, position, LENGTH);

		// �ړ������Z�o
		{
			if (!canUp && !canDown)
			{
				// �����_���ŏo��
				if (std::rand() % 2 == 0)
				{
					result = Dir::Up;
				}
				else
				{
					result = Dir::Down;
				}
			}
			else if (!canUp && canDown)
			{
				result = Dir::Up;
			}
			else if (canUp && !canDown)
			{
				result = Dir::Down;
			}
			else
			{
				result = Dir::Right;
			}
		}

		break;
	default:
		break;
	}

	// �����ύX
	switch (result)
	{
	case Dir::Up:
		rotation = { 0,0,0 };
		break;
	case Dir::Down:
		rotation = { 0,180,0 };
		break;
	case Dir::Right:
		rotation = { 0,90,0 };
		break;
	case Dir::Left:
		rotation = { 0,-90,0 };
		break;
	default:
		break;
	}

	return result;
}
