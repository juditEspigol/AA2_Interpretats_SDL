#pragma once
#include "EnemyPlane.h"

class BigGreenPlane : public EnemyPlane
{
private:
	float timeToStop; 
	float timeShooting; 

	virtual void UpdateMovementPattern(float dt);

	void DeathAnimation() override; 

public:
	BigGreenPlane(Transform* _playerTransform);
	virtual void Update(float dt) override;
};