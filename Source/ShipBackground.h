#pragma once
#include "GameObject.h"

class ShipBackGround : public GameObject
{
private:

	void Movement();

	float speed;

public:

	ShipBackGround();

	void Update(float dt) override;

	void StopMoving();
};