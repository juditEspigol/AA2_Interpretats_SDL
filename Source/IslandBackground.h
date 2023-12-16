#pragma once
#include "GameObject.h"

class IslandBackground : public GameObject
{
private:

	void Movement();

public:

	IslandBackground(float posX, float posY);
	void Update(float dt) override;

	void Die();
};