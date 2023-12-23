#pragma once
#include "GameObject.h"

// USE
#include "StatesShipBackground.h"
#include "ScoreManager.h"

class ShipBackGround : public GameObject
{
private:
	float speedY; 
	StateShipBackground currentState;
	bool isFinished; 

	void AddMovement(Vector2 _speed);

public:
	ShipBackGround();
	void Update(float _dt) override;
	void Finished() { isFinished = true; }
};