#pragma once
#include "GameObject.h"

//USE
#include "Spawner.h"
#include "EnemyBullet.h"
#include "ScoreManager.h"

// COLLISION
#include "PlayerBullet.h"

class EnemyPlane : public GameObject
{
protected:

	//Audio
	int shootId;
	int bulletId;

	bool isAlive; 
	int health;
	int score;
	Transform* playerTransform;

	float lastFireTime, fireTime; 
	float movementTime;

	Vector2 pixelsPorSecond; 

	void Shoot(); 

	bool IsPlayerBullet(Object* other); 
	bool IsOutOfWindow(); 

	void GetDamage(const int amount);

	virtual void UpdateMovementPattern(float dt) = 0; 

	//ANIMATIONS
	virtual void DeathAnimation() = 0;

	void DeathState(); 

public:
	EnemyPlane(int hp, int score, Transform* transform);
	~EnemyPlane()
	{
		AUDIO.FreeClip(shootId);
		AUDIO.FreeClip(bulletId);
	}

	virtual void Update(float dt) override; 
	void OnCollisionEnter(Object* other) override; 

	virtual void Destroy() override 
	{
		isAlive = false; 
		ChangeAnimation("Death");
		if (renderer->LastFrame() && !isPendingDestroy)
		{
			isPendingDestroy = true;
			SCORE.AddScore(score);
			SCORE.planesShootedDown++;
		}
	}
};