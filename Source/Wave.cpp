#include "Wave.h"

Wave::Wave(float _startTime, WaveType _waveType, Player* _player)
{
	startTime = _startTime;
	currentTime = 0;
	waveType = _waveType;
	
	planesAreSpawned = false;
	
	CreateWaves(_player);
}

void Wave::CreateWaves(Player* _player)
{
	switch (waveType)
	{
	case SmallNormal:
		CreateSmallNormal(_player);
		break;
	case SmallRed:
		CreateSmallRed(_player);
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

void Wave::CreateSmallNormal(Player* _player)
{
	amount = 4;

	for (int i = 0; i < amount; i++)
	{
		planesToSpawn.push_back(new SmallNormalPlane(SmallNormalPlane::MovementType::CURVE, true, _player->GetTransform()));
	}
}

void Wave::CreateSmallRed(Player* _player)
{
	amount = 5;

	powerUpToSpawn = new GrayPowerUp(_player);
	powerUpHasSpawned = false;


	for (int i = 0; i < amount; i++)
	{
		planesToSpawn.push_back(new SmallRedPlane(true, false, _player->GetTransform()));
	}
}

void Wave::CreateMediumYellow(Player* _player)
{
	amount = 2;

	for (int i = 0; i < amount; i++)
	{
		planesToSpawn.push_back(new MediumYellowPlane(false, _player->GetTransform()));
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

	if (IM.CheckKeyState(SDLK_k, PRESSED))
	{
		for (EnemyPlane* plane : planesToSpawn)
			plane->Destroy();
	}

	currentTime += _dt;

	if (currentTime >= startTime && !planesAreSpawned)
	{
		SpawnPlanes();
	}

	if (planesAreSpawned)
	{
		UpdatePlanes(_dt);
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

void Wave::UpdatePlanes(float _dt)
{
	for (EnemyPlane* e : planesToSpawn)
		e->Update(_dt);
}
