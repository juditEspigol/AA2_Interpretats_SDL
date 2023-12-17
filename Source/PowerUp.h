#pragma once
#include "GameObject.h"

class PowerUp : public GameObject
{
protected:

public:
	PowerUp()
	{

	}
	virtual void Update(float dt) override
	{
		GameObject::Update(dt); 
	}
	virtual void OnCollisionEnter(Object* object) override
	{

	}
};