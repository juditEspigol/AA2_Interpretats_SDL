#pragma once
#include "Scene.h"

// DEPENDENCIES
#include "HighScoreManager.h"
#include "Button.h"
#include "UserScore.h"

class Ranking : public Scene
{
public:
	Ranking();

	void OnEnter() override; 

	void Update(float dt) override;
};