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
	// �I�u�W�F�N�g�z��ɒǉ�
	objects.push_back(object);
}

void ObjectManager::Initialize(Input* input, TexCollision* texCol)
{
	for (auto x : objects)
	{
		x->Initialize(input, texCol);
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