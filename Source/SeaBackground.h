#pragma once
#include "GameObject.h"

class SeaBackground : public GameObject
{
private:

	float posToRestart;

	void Movement();

public:

	SeaBackground(float offset = 0);

	void Update(float dt) override;

	void ScrollFinished();
};