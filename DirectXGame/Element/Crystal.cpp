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
	// Ž€‚ñ‚¾‚ç’n‰º‘—‚è
	if (isDead)
	{
		position = { 0, -50, 0 };
	}

	crystalObj->SetPosition(position);
	crystalObj->Update();

	circleRot++;
	circleObj->SetPosition(position);
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
