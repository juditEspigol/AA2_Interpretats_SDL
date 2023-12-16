#pragma once
#include "EnemyPlane.h"

class SmallNormalPlane : public EnemyPlane
{
public: 
	enum MovementType { V, CURVE, STRAIGHT };

private:
	MovementType currentMove;
	bool isRight; 

	virtual void UpdateMovementPattern(float dt);

public:
	SmallNormalPlane(MovementType movement, bool isRight);
	virtual void Update(float dt) override; 
};