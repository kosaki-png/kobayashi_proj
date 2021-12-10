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