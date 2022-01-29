#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
	for (auto x : objects)
	{
		delete x;
	}
}

void ObjectManager::AddObject(Object* object)
{
	// オブジェクト配列に追加
	objects.push_back(object);
}

void ObjectManager::Initialize(Input* input, TexCollision* texCol)
{
	// 初期化と一度だけ更新
	for (auto x : objects)
	{
		x->Initialize(input, texCol);
		x->Update();
	}
}

void ObjectManager::Update(XMFLOAT3 playerPos, float length)
{
	// 範囲指定がないなら全て更新
	if (length == 0)
	{
		for (auto x : objects)
		{
			x->Update();
		}
	}
	else
	{
		for (auto x : objects)
		{
			// プレーヤーの指定範囲内なら更新
			if (abs(x->GetPosition().x - playerPos.x) < length ||
				abs(x->GetPosition().z - playerPos.z) < length)
			{
				x->Update();
			}
		}
	}
}

void ObjectManager::Draw(ID3D12GraphicsCommandList* cmdList, XMFLOAT3 playerPos, float length)
{
	// 範囲指定がないなら全て描画
	if (length == 0)
	{
		for (auto x : objects)
		{
			x->Draw(cmdList);
		}
	}
	else
	{
		for (auto x : objects)
		{
			// プレーヤーの指定範囲内なら更新
			if (abs(x->GetPosition().x - playerPos.x) < length ||
				abs(x->GetPosition().z - playerPos.z) < length)
			{
				x->Draw(cmdList);
			}
		}
	}
}

void ObjectManager::SpriteDraw()
{
	for (auto x : objects)
	{
		x->SpriteDraw();
	}
}
