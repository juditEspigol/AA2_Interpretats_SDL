#pragma once
#include "GameObject.h"
#include "Object.h"
#include "EnemyBullet.h"
#include "Spawner.h"
#include "Player.h"

class EnemyPlane : public GameObject
{
protected:

	Player* playerReference;

	int health;
	float iFrames, lastIFrames; 
	int score;

	float lastFireTime; 
	float fireTime; 
	Vector2 speed; 

	int movementStage;
	float movementTime;

	virtual void Shoot(); 

	bool IsPlayerBullet(Object* other); 

	void GetDamage(const int amount);

	virtual void UpdateMovementPattern(float dt) = 0; 

public:
	EnemyPlane(int hp, int score, Player* playerReference);
	virtual void Update(float dt) override; 
	void OnCollisionEnter(Object* other) override; 
};