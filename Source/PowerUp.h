#pragma once
#include "GameObject.h"
#include "Player.h"
#include "ScoreManager.h"

class PowerUp : public GameObject
{
protected:
	Player* player; 
	int speed; 
	int scoreToGive;
	int powerUpID;

public:
	PowerUp(Player* p); 

	void Update(float dt) override; 
	void AddMovement(); 

	void GiveScore();

	virtual void OnCollisionEnter(Object* other) override; 
	virtual bool IsPlayer(Object* other) = 0; 
	bool IsOutOfWindow(); 

	inline void SetPosition(const Vector2 pos) { transform->position = pos; }
};