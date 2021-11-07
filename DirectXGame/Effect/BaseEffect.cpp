#include "BaseEffect.h"

void BaseEffect::InStart(bool goOut)
{
	this->goOut = goOut;
	// スタートしていないならさせる
	if (!in)
	{
		count = 0;
		in = true;
	}
}

void BaseEffect::OutStart()
{
	// スタートしていないならさせる
	if (!out)
	{
		count = 0;
		out = true;
	}
}