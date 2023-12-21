#pragma once
#include "EnemyPlane.h"

class BigGreenPlane : public EnemyPlane
{
private:
	bool isGoingUp;
	Vector2 targetPos;

	float stopTime = 4.0f; 
	float timeShooting = 2.0f; 

	Vector2 pixelsPorSecond = Vector2(0, 1); 

	virtual void UpdateMovementPattern(float dt);

public:
	BigGreenPlane(Transform* _playerTransform);
	virtual void Update(float dt) override;
};