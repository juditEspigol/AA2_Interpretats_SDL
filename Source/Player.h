#pragma once
#include "GameObject.h"

// AGGREGATION
#include "PlayerBullet.h"
#include "SupportPlane.h"
#include "StatesPlayer.h"
// DEPENDENCY
#include "Spawner.h"
#include "InputManager.h"
#include "LivesManager.h"


class Player : public GameObject
{
private:
	StatesPlayer currentState; 
	StatesPlayer nextState; 
	int health; 
	float force;
	float fireTime, lastFireTime;

	int avaliableRolls;

	bool doubleFire; 
	std::vector<SupportPlane*> supportPlanes; 

	float movementTime = 0.0f; 
	int movementState = 0; 



	void UpdateSupportPlanes(float dt);

	void CheckStatePlayer(float dt); 

	void MoveInputs(); 
	void UpdateFlyingAnimation();
	inline void AddMovement(const Vector2 direction) { rb->AddForce(direction); }

	void ShootInputs(); 
	void Shoot();

	void Roll(StatesPlayer nextState);
	void RollAnimation();

	void TakeOff(); 

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

	inline int GetHealth() const { return health; }
	inline bool GetHasSupportPlanes() const { return supportPlanes.size() == 2; }
	inline bool GetDoubleFireEnabled()const { return doubleFire; }
};