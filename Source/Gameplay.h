#pragma once
#include <cassert>
#include "Scene.h"

// DEPENDENCIES
#include "ScoreManager.h"
#include "LivesManager.h"
#include "HighScoreManager.h"

// AGGREGATION
#include "Button.h"
#include "SeaBackground.h"
#include "IslandBackground.h"
#include "LevelLoader.h"
#include "Wave.h"
#include "Player.h"
#include "ShipBackground.h"
#include "LevelLoader.h"

enum StatesGameplay { GAME, PAUSE, FINISH_STATE, HIT, GAME_OVER };

class Gameplay : public Scene
{
private:
	float timeToSpawnIsland;
	float currentTimeToSpawnIsland;

	StatesGameplay currentState; 

	Player* player;
	ShipBackGround* ship; 

	std::vector<Wave*> remainingWaves;

	int sizeRemainingWaves;
	int levelWaves;

	int mainThemeId;
	int stageCompletedId;

	LevelLoader levelLoader;

	int currentKeyLevel;

public:

	Gameplay();
	virtual void OnEnter() override; 
	virtual void Render() override; 
	virtual void Update(float dt) override;

	void SpawnIsland();
};

