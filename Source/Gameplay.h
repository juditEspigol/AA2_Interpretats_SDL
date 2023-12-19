#pragma once
#include "Scene.h"
#include "ScoreManager.h"
#include "Player.h"
#include "SeaBackground.h"
#include "IslandBackground.h"

#include "Wave.h"

#include "GreenPowerUp.h"
#include "GrayPowerUp.h"
#include "WhitePowerUp.h"
#include "ShipBackground.h"

class Gameplay : public Scene
{
private:
	int sfxID;

	float timeToSpawnIsland;
	float currentTimeToSpawnIsland;

	Player* player;

	std::vector<Wave> remainingWaves;
	int sizeRemainingWaves;
	int levelWaves;

public:

	Gameplay();
	virtual void OnEnter() override; 
	virtual void Render() override; 
	virtual void Update(float dt) override;

	void SpawnIsland();
};

