#include "FlameRate.h"
#include "time.h"
#include <windows.h>
FlameRate::FlameRate()
{
	FPS = 60;//�Œ肵�����t���[�����[�g
	count = 0;//�t���[����
	startTime = 0;//�������J�n���Ă���̎��Ԃ̋L�^
}
void FlameRate::Update()
{
	if (count == 0)
	{
		startTime = clock();
	}
	if (count == 60)
	{
		startTime = clock();
		count = 0;
	}
	count++;
}
void FlameRate::Wait()
{
	TookTime = clock() - startTime;
	WaitTime = count * 1000 / FPS - TookTime;
	if (WaitTime > 0)
	{
		Sleep(WaitTime);
	}
}
