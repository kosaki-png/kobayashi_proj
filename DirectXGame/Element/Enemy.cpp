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
}

void Enemy::Update()
{
	enemyObj->Update();
}

void Enemy::Draw(ID3D12GraphicsCommandList* cmdList)
{
	enemyObj->Draw(cmdList, true);
}
