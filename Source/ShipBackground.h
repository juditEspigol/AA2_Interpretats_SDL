#pragma once
#include "GameObject.h"
#include "Player.h"
#include "StatesShipBackground.h"

class ShipBackGround : public GameObject
{
private:

	void Movement();

	float speed;

	StateShipBackground currentState;

	float pointToStopAtStarting;
	float pointToStopAtFinishing;

	Player* player;

	float timeToSetSail;
	float currentTime;

	bool hasToSetSail;

public:

	ShipBackGround(Player* player);

	void Update(float _dt) override;

	void StopMoving();

	void SetSail(float _dt);
	void SailFinished(float _dt);

	void ChangeState(StateShipBackground newState);
};