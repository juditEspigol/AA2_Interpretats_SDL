#pragma once
#include "GameObject.h"

// AGGREGATION
#include "PlayerBullet.h"
#include "SupportPlane.h"
#include "StatesPlayer.h"
// USE
#include "Spawner.h"
#include "InputManager.h"
#include "LivesManager.h"


class Player : public GameObject
{
private:
	StatesPlayer currentState; 
	int health; 
	float force;
	float fireTime, lastFireTime;

	bool doubleFire; 
	std::vector<SupportPlane*> supportPlanes; 



	void UpdateSupportPlanes(float dt);

	void CheckStatePlayer(); 

	

	void MoveInputs(); 
	void UpdateFlyingAnimation();
	inline void AddMovement(const Vector2 direction) { rb->AddForce(direction); }

	void ShootInputs(); 
	void Shoot();

	void Roll();
	void RollAnimation();

	void Death(); 
	void DeathAnimation(); 

	// COLLISIONS
	bool IsEnemyPlane(Object* other);
	bool IsEnemyBullet(Object* other);
	bool IsOutOfWindow(); 

	void GetDamage(const int amount);

	void LandingAnimation(); 
	void TakeOffAnimation(); 

	void CreateAnimations();

public:
	Player(); 
	void Update(float dt) override; 
	virtual void OnCollisionEnter(Object* other) override;

	void AddSupportPlanes();
	inline void EnableDoubleFire() { doubleFire = true; }

	void ChangeState(const StatesPlayer newState);

	inline int GetHealth() const { return health; }
};