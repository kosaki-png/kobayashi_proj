#include "Object.h"

Object::Object()
{
}

Object::~Object()
{
}

void Object::Initialize(Input* input)
{
	// nullptr�`�F�b�N
	assert(input);

	this->input = input;
}