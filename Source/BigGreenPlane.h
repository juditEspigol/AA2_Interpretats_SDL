#pragma once
#include "EnemyPlane.h"

class BigGreenPlane : public EnemyPlane
{
private:
	bool isGoingUp;
	Vector2 targetPos;

	virtual void UpdateMovementPattern(float dt);

public:
	BigGreenPlane();
	virtual void Update(float dt) override;
};