#pragma once
#include "EnemyPlane.h"

class SmallRedPlane : public EnemyPlane
{
private:
	bool isRight; 
	bool isLooping;

	virtual void UpdateMovementPattern(float dt);

public:
	SmallRedPlane();
	virtual void Update(float dt) override;
};