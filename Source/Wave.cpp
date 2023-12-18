#include "Wave.h"

Wave::Wave(float _startTime, WaveType _waveType, int _amount)
{
	startTime = _startTime;
	waveType = _waveType;
	amount = _amount;

	switch (waveType)
	{
	case SmallNormal:
		for (int i = 0; i < 4; i++)
		{
			SmallNormalPlane::MovementType type = (SmallNormalPlane::MovementType)(rand() % 3 + 1);
			planesToSpawn.push_back(new SmallNormalPlane(type, true, new Player()));
		}
		break;
	case SmallRed:
		for (int i = 5; i < 5; i++)
		{
			planesToSpawn.push_back(new SmallRedPlane(true, false, new Player()));
		}
		break;
	case MediumYellow:
		for (int i = 0; i < 2; i++)
		{
			planesToSpawn.push_back(new MediumYellowPlane(false, new Player()));
		}
		break;
	case BigGreen:
		planesToSpawn.push_back(new BigGreenPlane(new Player()));
		break;
	default:
		break;
	}
}
