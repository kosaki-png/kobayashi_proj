#include "BaseEffect.h"

void BaseEffect::InStart(bool goOut)
{
	this->goOut = goOut;
	// �X�^�[�g���Ă��Ȃ��Ȃ炳����
	if (!in)
	{
		count = 0;
		in = true;
	}
}

void BaseEffect::OutStart()
{
	// �X�^�[�g���Ă��Ȃ��Ȃ炳����
	if (!out)
	{
		count = 0;
		out = true;
	}
}