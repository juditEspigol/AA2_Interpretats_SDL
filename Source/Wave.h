#pragma once

#include "WaveType.h"
#include "MovementPattern.h"
#include "EnemyPlane.h"
#include "SmallNormalPlane.h"
#include "SmallRedPlane.h"
#include "MediumYellowPlane.h"
#include "BigGreenPlane.h"

class Wave : public GameObject
{
private:

	float startTime;
	float currentTime;
	WaveType waveType;
	MovementPattern movementPattern;
	int amount;
	std::vector<EnemyPlane*> planesToSpawn;

	bool isFinished;

public:

	Wave(float _startTime, WaveType _waveType, Transform* _playerTransform);

	void Update(float _dt);

	void Start();

	bool IsFinished();

	void SpawnPlanes();
};
