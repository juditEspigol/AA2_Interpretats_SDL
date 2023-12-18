#pragma once

#include "Spawner.h"
#include "WaveType.h"
#include "MovementPattern.h"
#include "EnemyPlane.h"
#include "SmallNormalPlane.h"
#include "SmallRedPlane.h"
#include "MediumYellowPlane.h"
#include "BigGreenPlane.h"

class Wave
{
private:

	float startTime;
	WaveType waveType;
	MovementPattern movementPattern;
	int amount;
	std::vector<EnemyPlane*> planesToSpawn;
	bool isFinished;

	

public:

	Wave(float _startTime, WaveType _waveType, int _amount);

	void Update(float dt, const Player* p, Spawner* spawner);

	void Start();

	bool IsFinished();
};
