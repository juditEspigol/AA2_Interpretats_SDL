#pragma once
#include "Spawner.h"
#include "GameObject.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "PlayerBullet.h"
#include "AnimatedImageRenderer.h"
#include "ScoreManager.h"
#include "SupportPlane.h"

class Player : public GameObject
{
private:
	bool isRolling;
	float force; 

	int health; 
	float iFrames, lastIFrames;

	float fireTime, lastFireTime;
	bool doubleFire; 
	std::vector<SupportPlane*> supportPlanes; 

	inline void AddMovement(const Vector2 dir) { rb->AddForce(dir); }
	void MovementInputs(); 

	void Shoot();
	void ShootInputs(); 

	bool IsEnemyPlane(Object* other);
	bool IsEnemyBullet(Object* other);

	void GetDamage(const int amount);

	void IdleAnimation(); 
	void RightAnimation(); 
	void LeftAnimation(); 
	void DeathAnimation();
	void RollAnimation(); 
	void LandingAnimation(); 
	void TakeOffAnimation(); 

	void CreateAnimations(); 

public:
	Player(); 
	void Update(float dt) override; 
	virtual void OnCollisionEnter(Object* other) override;

	void AddSupportPlanes();
	inline void EnableDoubleFire() { doubleFire = true; }
};