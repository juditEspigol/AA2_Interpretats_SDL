#pragma once
#include "EnemyPlane.h"
#include "Pattern.h"

class SmallRedPlane : public EnemyPlane
{
private:
	bool isRight; 
	bool isUp; 

	float startLoop; 
	float radiusLoop; 
	Pattern pattern;

	virtual void UpdateMovementPattern(float dt);

	Vector2 Loop(float dt, int cosSigne, int sinSigne);

	void DeathAnimation() override; 

	void BuildPattern(Pattern _pattern, float& posToSpawnY);

public:
	SmallRedPlane(Pattern _pattern, Transform* _playerTransform);
	virtual void Update(float dt) override;
};