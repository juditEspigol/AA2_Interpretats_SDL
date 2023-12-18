#include "Wave.h"

Wave::Wave(float _startTime, WaveType _waveType, int _amount, Transform* _playerTransform)
{
	startTime = _startTime;
	waveType = _waveType;
	amount = _amount;
	isFinished = false;


	switch (waveType)
	{
	case SmallNormal:
		for (int i = 0; i < 4; i++)
		{
			SmallNormalPlane::MovementType type = (SmallNormalPlane::MovementType)(rand() % 3 + 1);
			planesToSpawn.push_back(new SmallNormalPlane(type, true, _playerTransform));
		}
		break;
	case SmallRed:
		for (int i = 0; i < 5; i++)
		{
			planesToSpawn.push_back(new SmallRedPlane(true, false, _playerTransform));
		}
		break;
	case MediumYellow:
		for (int i = 0; i < 2; i++)
		{
			planesToSpawn.push_back(new MediumYellowPlane(false, _playerTransform));
		}
		break;
	case BigGreen:
		planesToSpawn.push_back(new BigGreenPlane(_playerTransform));
		break;
	default:
		break;
	}
}
