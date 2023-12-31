#include "Wave.h"

Wave::Wave(float _startTime, WaveType _waveType, Pattern _pattern, Player* _player)
{
	startTime = _startTime;
	currentTime = 0;
	waveType = _waveType;
	
	planesAreSpawned = false;
	
	CreateWaves(_player, _pattern);
}

void Wave::CreateWaves(Player* _player, Pattern _pattern)
{
	switch (waveType)
	{
	case SmallNormal:
		CreateSmallNormal(_player, _pattern);
		break;
	case SmallRed:
		CreateSmallRed(_player, _pattern);
		break;
	case MediumYellow:
		CreateMediumYellow(_player);
		break;
	case BigGreen:
		CreateBigGreen(_player);
		break;
	default:
		amount = 0;
		break;
	}
}

void Wave::CreateSmallNormal(Player* _player, Pattern _pattern)
{
	amount = 4;
	bool right = true; 

	for (int i = 0; i < amount; i++)
	{
		planesToSpawn.push_back(new SmallNormalPlane(_pattern, right, _player->GetTransform()));
		right = !right; 
	}
}

void Wave::CreateSmallRed(Player* _player, Pattern _pattern)
{
	amount = 5;

	int randomPowerUp = 1 + rand() % 3;

	if (randomPowerUp == 1)
		powerUpToSpawn = new GrayPowerUp(_player);
	else if (randomPowerUp == 2)
		powerUpToSpawn = new GreenPowerUp(_player);
	else
		powerUpToSpawn = new WhitePowerUp(_player);

	powerUpHasSpawned = false;
	float timeToWait = 0; 


	for (int i = 0; i < amount; i++)
	{
		planesToSpawn.push_back(new SmallRedPlane(_pattern, timeToWait, _player->GetTransform()));
		timeToWait += 0.25; 
	}
}

void Wave::CreateMediumYellow(Player* _player)
{
	amount = 2;

	bool isRight = true;

	for (int i = 0; i < amount; i++)
	{
		planesToSpawn.push_back(new MediumYellowPlane(isRight, _player->GetTransform()));
		isRight = false;
	}
}

void Wave::CreateBigGreen(Player* _player)
{
	amount = 1;
	planesToSpawn.push_back(new BigGreenPlane(_player->GetTransform()));
}

void Wave::Update(float _dt)
{
	DestroyPlanes();

	currentTime += _dt;

	if (currentTime >= startTime && !planesAreSpawned)
	{
		SpawnPlanes();
	}
}

void Wave::SpawnPlanes()
{
	int size = planesToSpawn.size();

	for (int i = 0; i < size; i++)
	{
		SPAWNER.SpawnObject(planesToSpawn[i]);
	}
	planesAreSpawned = true;
}

void Wave::DestroyPlanes()
{
	for (int i = planesToSpawn.size() - 1; i >= 0; i--)
	{
		if (planesToSpawn[i]->IsPendingDestroy())
		{
			planesToSpawn.erase(planesToSpawn.begin() + i);
		}
	}
	for(auto plane : planesToSpawn)
		posSpawnPowerUp = plane->GetPosition();

	if (waveType == WaveType::SmallRed && planesToSpawn.size() == 0 && !powerUpHasSpawned)
	{
 	 	powerUpHasSpawned = true;
		powerUpToSpawn->SetPosition(posSpawnPowerUp);
		SPAWNER.SpawnObject(powerUpToSpawn);
	}
}

void Wave::ForceDestroyPlanes()
{
	for (int i = planesToSpawn.size() - 1; i >= 0; i--)
		planesToSpawn.erase(planesToSpawn.begin() + i);

	planesToSpawn.clear();
}
