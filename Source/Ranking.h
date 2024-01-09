#pragma once
#include "Scene.h"
#include "HighScoreManager.h"

class Ranking : public Scene
{
public:
	Ranking();

	void OnEnter() override {};

	std::string OnExit() override {
		return "";
	};

	void Update(float dt) override {};
	void Render() override {};
};