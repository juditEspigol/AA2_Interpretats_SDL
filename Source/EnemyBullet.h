#pragma once
#include "GameObject.h"

class EnemyBullet : public GameObject
{
private:
	Vector2 speed;

public:
	EnemyBullet(Vector2 pos, Vector2 direction);
	virtual void Update(float dt) override;
};
