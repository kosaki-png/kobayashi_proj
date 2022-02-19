#include "Transition.h"

Transition::Transition()
{
}

void Transition::Start()
{
	// エフェクト初期化
	startCnt = 0;
	isEffect = true;
}
