#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
	for (int i = 0; i < objCnt; i++)
	{
		objects.pop_back();
	}
}

void ObjectManager::AddObject(Object* object)
{
	// オブジェクト配列に追加
	objects.push_back(object);
	objCnt++;
}

void ObjectManager::Initialize(Input* input)
{
	objKogakuin = new Fbx();
	objKogakuin->Initialize();
	objKogakuin->SetModel(ModelManager::GetInstance()->GetModel(0));

	for (auto x : objects)
	{
		x->Initialize(input);
	}
}

void ObjectManager::Update()
{
	//XMFLOAT4 a = texCol->GetPixelColor(0, { 1, 1 });
	//XMFLOAT4 b = texCol->GetPixelColor(0, { 1149, 899 });

	objKogakuin->Update();

	for (auto x : objects)
	{
		x->Update();
	}
}

void ObjectManager::Draw(ID3D12GraphicsCommandList* cmdList)
{
	objKogakuin->Draw(cmdList, false);
	//player->Draw(cmdList);

	for (auto x : objects)
	{
		x->Draw(cmdList);
	}
}