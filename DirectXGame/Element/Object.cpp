#include "Object.h"

Object::Object()
{
}

Object::~Object()
{
}

void Object::Initialize(Input* input, TexCollision* texCol)
{
	// nullptrチェック
	assert(input);
	assert(texCol);

	this->input = input;
	this->texCol = texCol;
}

void Object::Placement(TexCollision::ArgColor color)
{
	while (true)
	{
		// 座標セット
		position = { (float)(std::rand() % 3390), 0, (float)(std::rand() % 2775) };
		// そこが指定色なら配置完了
		if (texCol->GetHitFlag(color, position))
		{
			break;
		}
	}
}