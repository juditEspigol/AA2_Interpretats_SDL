#pragma once
#include "EnemyPlane.h"
#include "Pattern.h"

class SmallNormalPlane : public EnemyPlane
{
public: 
	enum MovementType { V = 0, CURVE = 1, STRAIGHT = 2, COUNT = 3 };

private:
	MovementType currentMove;
	bool isRight; 

	float changeMoveTime;
	float radiusLoop;

	void BuildPattern(Pattern _pattern);
	virtual void UpdateMovementPattern(float dt);

	void MovementV(float dt);  
	void MovementCurve(float dt); 
	void MovementStraight(float dt); 

	Vector2 Loop(float dt, int cosSigne, int sinSigne);

	// ANIMATIONS
	void DeathAnimation() override; 

public:
	SmallNormalPlane(Pattern _pattern, Transform* _playerTransform);
	virtual void Update(float dt) override; 
};