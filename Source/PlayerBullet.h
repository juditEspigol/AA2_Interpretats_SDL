#pragma once
#include "GameObject.h"

class PlayerBullet : public GameObject
{
private:
	bool hasCollisioned;
	Vector2 speed; 

public:
	PlayerBullet(Vector2 pos);

	virtual void Update(float dt) override; 
	void OnCollisionEnter(Object* other) {}
};

