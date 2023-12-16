#pragma once
#include "EnemyPlane.h"

class MediumYellowPlane : public EnemyPlane
{
private:
	bool isRight;
	bool isLooping;

	virtual void UpdateMovementPattern(float dt);

public:
	MediumYellowPlane();
	virtual void Update(float dt) override;
};