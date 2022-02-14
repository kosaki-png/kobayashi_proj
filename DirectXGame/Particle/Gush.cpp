#include "Gush.h"

Gush::Gush()
{
}

Gush::~Gush()
{
	delete cube.cubeObj;
}

void Gush::Initialize()
{
	cube.cubeObj = new Fbx();
	cube.cubeObj->Initialize({0, 1, 0});
	cube.cubeObj->SetModel(ModelManager::GetInstance()->GetModel(11));
	cube.cubeObj->SetScale({ 0.5f, 0.5f, 0.5f });


	Placement();
}

void Gush::Update()
{
	if (cube.cubePos.y > max)
	{
		Placement();
	}
	
	// 上昇
	cube.cubePos.y += speed;
	cube.cubeObj->SetPosition(cube.cubePos);

	cube.cubeObj->Update();
}

void Gush::Draw(ID3D12GraphicsCommandList* cmdList)
{
	cube.cubeObj->Draw(cmdList);
}

void Gush::Placement()
{
	// 座標セット
	cube.cubePos = { playerPos.x + (float)(mt() % 150) - 75.0f,
					 (float)(mt() % (int)abs(distance.y - distance.x)) + distance.x,
					 playerPos.z + (float)(mt() % 150) - 75.0f };
}