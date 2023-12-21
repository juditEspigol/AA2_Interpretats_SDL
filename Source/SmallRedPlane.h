#pragma once
#include "EnemyPlane.h"

class SmallRedPlane : public EnemyPlane
{
private:
	bool isRight; 
	bool isUp; 

	float startLoop; 
	float radiusLoop; 

	virtual void UpdateMovementPattern(float dt);

	Vector2 Loop(float dt, int cosSigne, int sinSigne);

	void DeathAnimation() override; 

public:
	SmallRedPlane(bool _isRight, bool _isUp, float posToSpawnY, Transform* _playerTransform);
	virtual void Update(float dt) override;
};