#include "Object.h"

Object::Object()
{
}

Object::~Object()
{
}

void Object::Initialize(Input* input)
{
	// nullptrチェック
	assert(input);

	this->input = input;
}