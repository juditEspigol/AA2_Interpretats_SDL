#pragma once
#include "Scene.h"
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