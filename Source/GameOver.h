#pragma once
#include "Scene.h"

// DEPENDENCIES
#include "HighScoreManager.h"
#include "Button.h"
#include "UserScore.h"

class GameOver : public Scene
{
public:
	GameOver(); 

	void OnEnter() override; 

	void Update(float dt) override;
};