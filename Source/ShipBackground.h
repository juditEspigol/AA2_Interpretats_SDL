#pragma once
#include "GameObject.h"

class ShipBackGround : public GameObject
{
private:

	void Movement();

public:

	ShipBackGround();

	void Update(float dt) override;

	void StopMoving();
};