#pragma once

#include "WaveType.h"
#include "MovementPattern.h"
#include "EnemyPlane.h"
#include "SmallNormalPlane.h"
#include "SmallRedPlane.h"
#include "MediumYellowPlane.h"
#include "BigGreenPlane.h"
#include "WhitePowerUp.h"
#include "GreenPowerUp.h"
#include "GrayPowerUp.h"
#include "Player.h"

class Wave : public GameObject
{
private:

	float startTime;
	float currentTime;
	WaveType waveType;
	MovementPattern movementPattern;
	int amount;
	std::vector<EnemyPlane*> planesToSpawn;


	bool planesAreSpawned;

	Vector2 posSpawnPowerUp; 
	PowerUp* powerUpToSpawn;
	bool powerUpHasSpawned;

public:

	Wave(float _startTime, WaveType _waveType, Player* _player);

	void CreateWaves(Player* _player);

	void CreateSmallNormal(Player* _player);

	void CreateSmallRed(Player* _player);

	void CreateMediumYellow(Player* _player);

	void CreateBigGreen(Player* _player);

	void Update(float _dt);

	void SpawnPlanes();

	void DestroyPlanes();

	void UpdatePlanes(float _dt);
};
