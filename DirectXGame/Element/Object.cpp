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