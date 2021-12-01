#include "BaseEffect.h"

void BaseEffect::InStart()
{
	// スタートしていないならさせる
	if (!in)
	{
		count = 0;
		isEffect = true;
		in = true;
	}
}

void BaseEffect::OutStart()
{
	// スタートしていないならさせる
	if (!out)
	{
		count = 0;
		isEffect = true;
		out = true;
	}
}