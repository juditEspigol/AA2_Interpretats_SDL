#pragma once
#include "Spawner.h"
#include "GameObject.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "PlayerBullet.h"
#include "AnimatedImageRenderer.h"

class Player : public GameObject
{
private:
	bool isRolling;
	float force; 

	int health; 
	float iFrames, lastIFrames;

	float fireTime, lastFireTime;
	bool doubleFire; 
	//std::vector<SupportPlane> supportPlanes; 

	inline void AddMovement(Vector2 dir) { rb->AddForce(dir); }
	void MovementInputs(); 

	void Shoot();
	void ShootInputs(); 

	bool IsEnemyPlane(Object* other);
	bool IsPlayerBullet(Object* other);

	void GetDamage(const int amount);

	void PlayDeathAnimation();
	void PlayRollAnimation(); 
	void PlayLandingAnimation(); 
	void PlayTakeOffAnimation(); 
	void EnableDoubleFire(); 
	void AddSupportPlanes(); 

public:
	Player(); 
	void Update(float dt) override; 
	virtual void OnCollisionEnter(Object* other) override;
};