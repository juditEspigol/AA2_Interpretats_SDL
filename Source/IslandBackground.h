#pragma once
#include "GameObject.h"

class IslandBackground : public GameObject
{
private:

	void Movement();

public:

	IslandBackground(Vector2 pos);
	void Update(float dt) override;
};