#pragma once
#include "GameObject.h"

class WaterBackGround : public GameObject
{
private:

	float posToRestart;

	void Movement();

public:

	WaterBackGround(float offset = 0);
	void Update(float dt) override;

	void ScrollFinished();
};