#pragma once
#include "EnemyPlane.h"

class SmallRedPlane : public EnemyPlane
{
private:
	bool isRight; 
	bool isUp; 

	bool isLooping;
	float startLoop; 

	Vector2 pixelsPorSecond = Vector2(3, 0); 
	float radiusLoop = 10; 

	virtual void UpdateMovementPattern(float dt);

	Vector2 Loop(float dt, int cosSigne, int sinSigne);

public:
	SmallRedPlane(bool _isRight, bool _isUp, Transform* _playerTransform);
	virtual void Update(float dt) override;
};