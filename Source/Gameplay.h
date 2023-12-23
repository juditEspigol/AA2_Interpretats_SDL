#pragma once

#include <cassert>
#include "Scene.h"
#include "ScoreManager.h"
#include "LivesManager.h"
#include "Player.h"
#include "SeaBackground.h"
#include "IslandBackground.h"

#include "Wave.h"

#include "GreenPowerUp.h"
#include "GrayPowerUp.h"
#include "WhitePowerUp.h"
#include "ShipBackground.h"
#include "LevelLoader.h"

class Gameplay : public Scene
{
private:
	

	float timeToSpawnIsland;
	float currentTimeToSpawnIsland;

	Player* player;
	ShipBackGround* ship; 

	std::vector<Wave> remainingWaves;
	int sizeRemainingWaves;
	int levelWaves;

	int mainThemeId;
	int stageCompletedId;

public:

	Gameplay();
	virtual void OnEnter() override; 
	virtual void Render() override; 
	virtual void Update(float dt) override;

	void SpawnIsland();
};

