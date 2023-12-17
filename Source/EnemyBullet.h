#pragma once
#include "GameObject.h"
#include "Player.h"

class EnemyBullet : public GameObject
{
private:

	Player* player;

	Vector2 speed;

	Vector2 directionToShoot;

public:

	EnemyBullet(Vector2 pos, Player* _playerReference);

	virtual void Update(float dt) override;
};
