#pragma once
#include "EnemyPlane.h"

class MediumYellowPlane : public EnemyPlane
{
private:
	bool isRight;
	bool isLooping;
	float startLoop; 

	virtual void UpdateMovementPattern(float dt);

public:
	MediumYellowPlane(bool isRight);
	virtual void Update(float dt) override;
};