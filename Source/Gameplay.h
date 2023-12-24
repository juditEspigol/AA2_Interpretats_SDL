#pragma once
#include <cassert>
#include "Scene.h"

// DEPENDENCIES
#include "ScoreManager.h"
#include "LivesManager.h"

// AGGREGATION
#include "SeaBackground.h"
#include "IslandBackground.h"
#include "LevelLoader.h"
#include "Wave.h"
#include "Player.h"
#include "ShipBackground.h"

class Gameplay : public Scene
{
private:
	float timeToSpawnIsland;
	float currentTimeToSpawnIsland;

	Player* player;
	ShipBackGround* ship; 

	int currentLevel;

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

