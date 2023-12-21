#pragma once
#include "EnemyPlane.h"

class MediumYellowPlane : public EnemyPlane
{
private:
	bool isRight;
	float startLoop; 

	Vector2 pixelsPorSecond;
	Vector2 radiusLoop;

	virtual void UpdateMovementPattern(float dt);

	Vector2 Loop(float dt, int cosSigne, int sinSigne);

public:
	MediumYellowPlane(bool _isRight, Transform* _playerTransform);
	virtual void Update(float dt) override;
};