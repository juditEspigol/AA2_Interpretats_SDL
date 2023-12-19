#pragma once
#include "GameObject.h"
#include "Player.h"

class PowerUp : public GameObject
{
protected:
	Player* player; 
	int speed; 

public:
	PowerUp(Player* p); 

	void Update(float dt) override; 
	void AddMovement(); 

	virtual void OnCollisionEnter(Object* other) override; 
	virtual bool IsPlayer(Object* other) = 0; 
	bool IsOutOfWindow(); 
};