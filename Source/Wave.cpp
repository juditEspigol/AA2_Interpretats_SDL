#include "Wave.h"

Wave::Wave(float _startTime, WaveType _waveType, Transform* _playerTransform)
{
	startTime = _startTime;
	currentTime = 0;
	waveType = _waveType;
	
	isFinished = false;
	
	switch (waveType)
	{
	case SmallNormal:
		amount = 4;
		// This region is in a Specific Block because you can't initialize a variable in a switch only in one case
		{
			//int type = (rand() % SmallNormalPlane::MovementType::COUNT + 1);

			for (int i = 0; i < amount; i++)
			{
				planesToSpawn.push_back(new SmallNormalPlane(SmallNormalPlane::MovementType::CURVE, true, _playerTransform));
			}
		}
		break;
	case SmallRed:
		amount = 5;
		for (int i = 0; i < amount; i++)
		{
			planesToSpawn.push_back(new SmallRedPlane(true, false,120, _playerTransform));
		}
		break;
	case MediumYellow:
		amount = 2;
		for (int i = 0; i < amount; i++)
		{
			planesToSpawn.push_back(new MediumYellowPlane(false, _playerTransform));
		}
		break;
	case BigGreen:
		amount = 1;
		planesToSpawn.push_back(new BigGreenPlane(_playerTransform));
		break;
	default:
		amount = 0;
		break;
	}
}

void Wave::Update(float _dt)
{
	for (int i = planesToSpawn.size() - 1; i >= 0; i--)
	{
		if (planesToSpawn[i]->IsPendingDestroy())
		{
			planesToSpawn.erase(planesToSpawn.begin() + i);
		}
	}

	currentTime += _dt;

	if (currentTime >= startTime && !isFinished)
	{
		isFinished = true;
		SpawnPlanes();
	}

	if (isFinished)
	{
		for (EnemyPlane* e : planesToSpawn)
			e->Update(_dt);
	}
}

void Wave::SpawnPlanes()
{
	int size = planesToSpawn.size();

	for (int i = 0; i < size; i++)
	{
		SPAWNER.SpawnObject(planesToSpawn[i]);
	}
}
