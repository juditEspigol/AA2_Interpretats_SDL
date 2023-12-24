#pragma once
#include "GameObject.h"

// AGGREGATION
#include "PlayerBullet.h"
#include "SupportPlane.h"
#include "StatesPlayer.h"
#include "ShipBackground.h"
// DEPENDENCY
#include "Spawner.h"
#include "InputManager.h"
#include "LivesManager.h"
#include "AudioManager.h"


class Player : public GameObject
{
private:

	//Audio
	int shootID;
	int CollisionId;
	int bulletId;
	int loseStageId;


	ShipBackGround* ship; 
	StatesPlayer currentState; 
	StatesPlayer nextState; 
	int health; 
	float force;
	float fireTime, lastFireTime;

	int avaliableRolls;

	bool doubleFire; 
	std::vector<SupportPlane*> supportPlanes; 

	float movementTime; 
	int movementState; 
	bool playerHitted = false; 

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
	Player(ShipBackGround* _ship);
	~Player() {
		AUDIO.FreeClip(shootID);
		AUDIO.FreeClip(CollisionId);
		AUDIO.FreeClip(loseStageId);
		AUDIO.FreeClip(bulletId);
	}
	void Update(float dt) override; 
	virtual void OnCollisionEnter(Object* other) override;

	void AddSupportPlanes();
	inline void EnableDoubleFire() { doubleFire = true; }

	inline int GetHealth() const { return health; }
	inline bool GetHasSupportPlanes() const { return supportPlanes.size() == 2; }
	inline bool GetDoubleFireEnabled()const { return doubleFire; }
	inline bool IsPlayerPaused() const { return currentState == STOP;  }
	inline bool PlayerHitted() const { return playerHitted; }
	void Reset()
	{
		currentState = TAKE_OFF;
		nextState = FLYING;
		health = LIVES_GAME.GetLives();
		doubleFire = false;
		movementTime = 0; 
		movementState = 0; 
		avaliableRolls = 3;
		playerHitted = false; 

		transform->position = Vector2(RENDERER.GetSizeWindow().x * 0.5, RENDERER.GetSizeWindow().y);
	}
};