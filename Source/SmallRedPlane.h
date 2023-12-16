#pragma once
#include "EnemyPlane.h"

class SmallRedPlane : public EnemyPlane
{
private:
	bool isRight; 
	bool isUp; 

	bool isLooping;
	float startLoop; 

	virtual void UpdateMovementPattern(float dt);

public:
	SmallRedPlane(bool isRight, bool isUp);
	virtual void Update(float dt) override;
};