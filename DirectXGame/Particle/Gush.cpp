#include "Gush.h"

Gush::Gush()
{
}

Gush::~Gush()
{
	for (auto x : cube)
	{
		delete x.cubeObj;
	}
}

void Gush::Initialize()
{
	for (int i = 0; i < CUBE_COUNT; i++)
	{
		cube[i].cubeObj = new Fbx();
		cube[i].cubeObj->Initialize({0, 1, 0});
		cube[i].cubeObj->SetModel(ModelManager::GetInstance()->GetModel(5));
		cube[i].cubeObj->SetScale({ 0.4f - 0.1f * i, 0.4f - 0.1f * i , 0.4f - 0.1f * i });
		cube[i].rotSpeed = { (float)(std::rand() % 5 + 2.0f), (float)(std::rand() % 5 - 2.0f) , (float)(std::rand() % 5 + 2.0f) };
	}
}

void Gush::Update()
{
	XMFLOAT3 tmpRot;

	if (cube[0].cubePos.y > 5)
	{
		Placement();
	}

	for (int i = 0; i < CUBE_COUNT; i++)
	{
		cube[i].cubePos.y += 0.05f;
		cube[i].cubeObj->SetPosition(cube[i].cubePos);
		tmpRot = cube[i].cubeObj->GetRotation();
		cube[i].cubeObj->SetRotation({ tmpRot.x += cube[i].rotSpeed.x, tmpRot.y += cube[i].rotSpeed.y , tmpRot.z += cube[i].rotSpeed.z });

		cube[i].cubeObj->Update();
	}
}

void Gush::Draw(ID3D12GraphicsCommandList* cmdList)
{
	for (int i = 0; i < CUBE_COUNT; i++)
	{
		if (cube[i].cubePos.y < 5)
		{
			cube[i].cubeObj->Draw(cmdList, true);
		}
	}
}

void Gush::Placement()
{
	// 座標セット
	position = { playerPos.x + (float)(std::rand() % 100) - 50, 
				 -(float)(std::rand() % 5),
				 playerPos.z + (float)(std::rand() % 100) - 50 };

	for (int i = 0; i < CUBE_COUNT; i++)
	{
		cube[i].cubePos = { position.x, position.y - 0.5f * i, position.z };
	}
}