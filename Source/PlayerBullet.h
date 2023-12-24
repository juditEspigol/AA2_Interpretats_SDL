#pragma once
#include "GameObject.h"

class PlayerBullet : public GameObject
{
private:
	Vector2 speed; 

public:
	PlayerBullet(Vector2 pos);
	virtual void Update(float dt) override;
};

