#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
	objects.clear();
}

void ObjectManager::AddObject(Object* object)
{
	// オブジェクト配列に追加
	objects.push_back(object);
}

void ObjectManager::Initialize(Input* input)
{
	for (auto x : objects)
	{
		x->Initialize(input);
	}
}

void ObjectManager::Update()
{
	for (auto x : objects)
	{
		x->Update();
	}
}

void ObjectManager::Draw(ID3D12GraphicsCommandList* cmdList)
{
	for (auto x : objects)
	{
		x->Draw(cmdList);
	}
}