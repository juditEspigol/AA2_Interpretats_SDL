#pragma once
#include "GameObject.h"
#include "Object.h"

class EnemyPlane : public GameObject
{
protected:
	int health;
	int score;
	int movementStage;
	float movementTime;

	virtual void Shoot(); 
	virtual void OnCollisionEnter(Object* other) {}

public:
	EnemyPlane(int hp, int score); 
	virtual void Update(float dt) override {}
};