#pragma once
#include "EnemyPlane.h"

class SmallNormalPlane : public EnemyPlane
{
public: 
	enum MovementType { V, CURVE, STRAIGHT };
	MovementType currentMove;

private:
	virtual void UpdateMovementPattern(float dt);

public:
	SmallNormalPlane();
	virtual void Update(float dt) override; 
};