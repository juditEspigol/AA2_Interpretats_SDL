#include "ShipBackground.h"

void ShipBackGround::Movement()
{
	rb->SetVeclocity(Vector2(0, speed));
}

ShipBackGround::ShipBackGround(Player* _player)
{
	speed = -16;

	currentState = StateShipBackground::STARTING;

	pointToStopAtStarting = 320;
	pointToStopAtFinishing = -320;

	player = _player;

	timeToSetSail = 5;
	currentTime = 0;
	hasToSetSail = false;

	//TRANSFORM
	transform = new Transform();
	transform->position = Vector2(RENDERER.GetSizeWindow().x * 0.5 - 95, RENDERER.GetSizeWindow().y - 10);
	transform->angle = 0.0f;
	transform->scale = Vector2(1.0f, 1.0f);
	transform->size = Vector2(63 * 3, 170* 3);
	transform->centered = false;

	//RENDER
	renderer = new ImageRenderer(transform, Vector2(0, 801), Vector2(63, 170));

	//RIGIDBODY
	rb = new RigidBody(transform);
}

void ShipBackGround::Update(float _dt)
{
	Object::Update(_dt);

	switch (currentState)
	{
	case STARTING:
		Movement();
		StopMoving();
		if (hasToSetSail)
			SetSail(_dt);
		break;
	case FINISHING:
		Movement();
		StopMoving();
		if (hasToSetSail)
			SetSail(_dt);
		break;
	default:
		break;
	}
}

void ShipBackGround::StopMoving()
{
	switch (currentState)
	{
	case STARTING:
		if (transform->position.y <= pointToStopAtStarting)
		{
			speed = 0;
			player->ChangeState(StatesPlayer::FLYING);
			hasToSetSail = true;
		}
		break;
	case FINISHING:
		if (transform->position.y >= pointToStopAtFinishing)
		{
			speed = 0;
			player->ChangeState(StatesPlayer::LANDED);
			hasToSetSail = true;
		}
		break;
	default:
		break;
	}
	
}

void ShipBackGround::SetSail(float _dt)
{
	currentTime += _dt;
	std::cout << currentTime << " " << timeToSetSail << std::endl;

	if (currentTime >= timeToSetSail)
	{
		if (currentState == StateShipBackground::STARTING)
			speed = 16;
		else
			speed = -16;
	}

	if (transform->position.y >= RENDERER.GetSizeWindow().y + 5)
	{
		std::cout << "Get out of the window" << std::endl;
		speed = 0;
		ChangeState(StateShipBackground::FINISHING);
	}
}

void ShipBackGround::ChangeState(StateShipBackground newState)
{
	switch (currentState)
	{
	case STARTING:
		speed = 0;
		hasToSetSail = false;
		break;
	case FINISHING:
		break;
	default:
		break;
	}

	switch (newState)
	{
	case STARTING:
		break;
	case FINISHING:
		transform->position.y = 0 - transform->size.y;
		speed = 16;
		break;
	default:
		break;
	}
	currentState = newState;
}
