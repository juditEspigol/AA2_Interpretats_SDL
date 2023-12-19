#pragma once
#include "GameObject.h"
#include "Player.h"

class PowerUp : public GameObject
{
protected:
	Player* player; 

public:
	PowerUp(Player* p)
		: player(p) {}
	void Update(float dt) override
	{
		GameObject::Update(dt); 
	}
	virtual void OnCollisionEnter(Object* other) override
	{
		if (rb->CheckCollision(other->GetRigidBody()))
		{
			if (IsPlayer(other))
				return;
		}
	}

	virtual bool IsPlayer(Object* other)
	{
		return false; 
	}
};