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
	// �I�u�W�F�N�g�z��ɒǉ�
	objects.push_back(object);
}

void ObjectManager::Initialize(Input* input, TexCollision* texCol)
{
	// �������ƈ�x�����X�V
	for (auto x : objects)
	{
		x->Initialize(input, texCol);
		x->Update();
	}
}

void ObjectManager::Update(XMFLOAT3 playerPos, float length)
{
	// �͈͎w�肪�Ȃ��Ȃ�S�čX�V
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
			// �v���[���[�̎w��͈͓��Ȃ�X�V
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
	// �͈͎w�肪�Ȃ��Ȃ�S�ĕ`��
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
			// �v���[���[�̎w��͈͓��Ȃ�X�V
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
