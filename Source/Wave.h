#pragma once
#include "WaveType.h"
#include "Pattern.h"

// ENEMY PLANES
#include "SmallNormalPlane.h"
#include "SmallRedPlane.h"
#include "MediumYellowPlane.h"
#include "BigGreenPlane.h"

// POWER UPS
#include "WhitePowerUp.h"
#include "GreenPowerUp.h"
#include "GrayPowerUp.h"

// PLAYER
#include "Player.h"

class Wave : public GameObject
{
private:

	float startTime;
	float currentTime;
	WaveType waveType;
	Pattern movementPattern;
	int amount;
	std::vector<EnemyPlane*> planesToSpawn;

	bool planesAreSpawned;

	Vector2 posSpawnPowerUp; 
	PowerUp* powerUpToSpawn;
	bool powerUpHasSpawned;

public:

	Wave(float _startTime, WaveType _waveType, Pattern _pattern, Player* _player);

	void CreateWaves(Player* _player, Pattern _pattern);

	void CreateSmallNormal(Player* _player, Pattern _pattern);

	void CreateSmallRed(Player* _player, Pattern _pattern);

	void CreateMediumYellow(Player* _player);

	void CreateBigGreen(Player* _player);

	void Update(float _dt);

	void SpawnPlanes();

	void DestroyPlanes();

	inline bool WaveDone() { return planesAreSpawned && planesToSpawn.empty(); }
};
