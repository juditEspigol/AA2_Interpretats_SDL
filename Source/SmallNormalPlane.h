#pragma once
#include "EnemyPlane.h"

class SmallNormalPlane : public EnemyPlane
{
public: 
	enum MovementType { V = 0, CURVE = 1, STRAIGHT = 2, COUNT = 3 };

private:
	MovementType currentMove;
	bool isRight; 

	virtual void UpdateMovementPattern(float dt);

public:
	SmallNormalPlane(MovementType _movement, bool _isRight, Transform* _playerTransform);
	virtual void Update(float dt) override; 
};