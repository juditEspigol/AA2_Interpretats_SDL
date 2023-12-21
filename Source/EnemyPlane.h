#pragma once
#include "GameObject.h"
#include "Object.h"
#include "EnemyBullet.h"
#include "Spawner.h"
#include "ScoreManager.h"

const float PI = 3.14159265359;

class EnemyPlane : public GameObject
{
protected:
	int health;
	int score;
	Transform* playerTransform;

	float lastFireTime, fireTime; 
	Vector2 speed; 

	int movementStage;
	float movementTime;

	void Shoot(); 

	bool IsPlayerBullet(Object* other); 
	bool IsOutOfWindow(); 

	void GetDamage(const int amount);

	virtual void UpdateMovementPattern(float dt) = 0; 

	//ANIMATIONS
	virtual void DeathAnimation() {};

public:
	EnemyPlane(int hp, int score, Transform* transform);
	virtual void Update(float dt) override; 
	void OnCollisionEnter(Object* other) override; 

	virtual void Destroy() override 
	{
		isPendingDestroy = true; 
		SCORE.AddScore(score);
	}
};