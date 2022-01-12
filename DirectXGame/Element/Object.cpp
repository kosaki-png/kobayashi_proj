#include "Object.h"

Object::Object()
{
}

Object::~Object()
{
}

void Object::Initialize(Input* input, TexCollision* texCol)
{
	// nullptr�`�F�b�N
	assert(input);
	assert(texCol);

	this->input = input;
	this->texCol = texCol;
}

void Object::Placement(TexCollision::ArgColor color)
{
	while (true)
	{
		// ���W�Z�b�g
		position = { (float)(std::rand() % 3390), 0, (float)(std::rand() % 2775) };
		// �������w��F�Ȃ�z�u����
		if (texCol->GetHitFlag(color, position))
		{
			break;
		}
	}
}