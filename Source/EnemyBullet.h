#pragma once
#include "GameObject.h"
#include "Player.h"

class EnemyBullet : public GameObject
{
private:

	Vector2 speed;

	Vector2 directionToShoot;

public:

	EnemyBullet(Vector2 pos, Vector2 _posToGo);

	virtual void Update(float dt) override;
};
