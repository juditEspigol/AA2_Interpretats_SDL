#pragma once
#include "Scene.h"

class Ranking : public Scene
{
private:

	void LoadScores();
public:
	Ranking() = default;

	void OnEnter() override;
	std::string OnExit() override;
	void Update(float dt) override;
	void Render() override;
};