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

	inline void AddMovement(Vector2 dir) { rb->AddForce(dir); }
	void MovementInputs(); 

	void Shoot();
	void ShootInputs(); 

	bool IsEnemyPlane(Object* other);
	bool IsEnemyBullet(Object* other);

	void GetDamage(const int amount);

	void PlayDeathAnimation();
	void PlayRollAnimation(); 
	void PlayLandingAnimation(); 
	void PlayTakeOffAnimation(); 
	void EnableDoubleFire(); 
	inline void AddSupportPlanes()
	{ 
		SupportPlane* support = new SupportPlane(Vector2(transform->size.x * 2, 0), transform->position);
		SPAWNER.SpawnObject(support);
		supportPlanes.push_back(support);

		SupportPlane* support2 = new SupportPlane(Vector2(-(transform->size.x * 2), 0), transform->position);
		SPAWNER.SpawnObject(support2);
		supportPlanes.push_back(support2);
	}

	void CreateAnimations(); 

public:
	Player(); 
	void Update(float dt) override; 
	virtual void OnCollisionEnter(Object* other) override;
};