#pragma once
#include "Scene.h"
#include "Player.h"
#include "WaterBackground.h"
#include "IslandBackground.h"
#include "SmallNormalPlane.h"
#include "SmallRedPlane.h"
#include "MediumYellowPlane.h"
#include "BigGreenPlane.h"

class Gameplay : public Scene
{
private:
	int sfxID;

	float timeToSpawnIsland;
	float currentTimeToSpawnIsland;

public:
	Gameplay();
	virtual void OnEnter() override;
	virtual void Render() override; 
	virtual void Update(float dt) override;

	void SpawnIsland();
};

