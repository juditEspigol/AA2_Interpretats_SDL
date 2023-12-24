#pragma once
#include "GameObject.h"

// DEPENDENCY
#include "StatesShipBackground.h"

class ShipBackGround : public GameObject
{
private:
	float speedY; 
	StateShipBackground currentState;
	bool isFinished; 
	bool playerCanLand; 

	void AddMovement(Vector2 _speed);

public:
	ShipBackGround();
	void Update(float _dt) override;
	void Finished() { isFinished = true; }

	bool GetPlayerCanLand() const { return playerCanLand; }
	void PlayerLanded() { playerCanLand = false;  }
};