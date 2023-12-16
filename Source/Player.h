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
	float fireTime; 
	float lastFireTime;

	AnimatedImageRenderer* animImageRenderer; 

	bool doubleFire; 
	//std::vector<SupportPlane> supportPlanes; 

	inline void AddMovement(Vector2 dir) { rb->AddForce(dir); }
	void MovementInputs(); 
	void Shoot();
	void ShootInputs(); 

	void PlayDeathAnimation();
	void PlayRollAnimation(); 
	void PlayLandingAnimation(); 
	void PlayTakeOffAnimation(); 
	void EnableDoubleFire(); 
	void AddSupportPlanes(); 

	virtual void OnCollisionEnter(Object* other) {}

public:
	Player(); 
	void Update(float dt) override; 
};