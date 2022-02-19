#include "Crystal.h"

Crystal::Crystal()
{
}

Crystal::~Crystal()
{
	delete crystalObj;
	delete circleObj;
}

void Crystal::Initialize(Input* input, TexCollision* texCol)
{
	Object::Initialize(input, texCol);

	crystalObj = new Fbx();
	crystalObj->Initialize();
	crystalObj->SetModel(ModelManager::GetInstance()->GetModel(3));

	circleObj = new Fbx();
	circleObj->Initialize();
	circleObj->SetModel(ModelManager::GetInstance()->GetModel(4));

	Placement(TexCollision::ArgColor::Red);
}

void Crystal::Update()
{
	// 死んだら地下送り
	if (isDead)
	{
		position = { 0, -50, 0 };
	}

	// 上下させる
	rot += 0.02f;

	// 本体
	rotation.y--;
	crystalObj->SetRotation(rotation);
	crystalObj->SetPosition({ position.x, position.y + sinf(rot) / 2, position.z });
	crystalObj->Update();

	// 周りの円回転
	circleRot++;
	circleObj->SetPosition({ position.x, position.y + sinf(rot) / 2, position.z });
	circleObj->SetRotation({ 0,circleRot,0 });
	circleObj->Update();
}

void Crystal::Draw(ID3D12GraphicsCommandList* cmdList)
{
	crystalObj->Draw(cmdList);
	circleObj->Draw(cmdList);
}

void Crystal::SpriteDraw()
{
}
