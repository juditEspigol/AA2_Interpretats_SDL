#pragma once
#include "Scene.h"
#include "Player.h"
#include "WaterBackground.h"
#include "IslandBackground.h"

class Gameplay : public Scene
{
private:
	int sfxID;

public:
	Gameplay();
	virtual void OnEnter() override;
	virtual void Render() override; 
	virtual void Update(float dt) override;

	void SpawnIsland();
};

