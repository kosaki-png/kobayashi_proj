#include "BaseEffect.h"

void BaseEffect::InStart()
{
	// �X�^�[�g���Ă��Ȃ��Ȃ炳����
	if (!in)
	{
		count = 0;
		isEffect = true;
		in = true;
	}
}

void BaseEffect::OutStart()
{
	// �X�^�[�g���Ă��Ȃ��Ȃ炳����
	if (!out)
	{
		count = 0;
		isEffect = true;
		out = true;
	}
}