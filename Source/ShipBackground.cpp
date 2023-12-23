#include "ShipBackground.h"

ShipBackGround::ShipBackGround()
	: speedY(30), currentState(StateShipBackground::STARTING), isFinished(false)
{
	//TRANSFORM
	transform = new Transform();
	transform->position = Vector2(RENDERER.GetSizeWindow().x * 0.5 - 95, RENDERER.GetSizeWindow().y * 0.25);
	transform->angle = 0.0f;
	transform->scale = Vector2(1.0f, 1.0f);
	transform->size = Vector2(63 * 3, 170* 3);
	transform->centered = false;

	//RENDER
	renderer = new ImageRenderer(transform, Vector2(0, 801), Vector2(63, 170));

	//RIGIDBODY
	rb = new RigidBody(transform);
}

void ShipBackGround::AddMovement(Vector2 _speed)
{
	rb->SetVeclocity(_speed);
}


void ShipBackGround::Update(float _dt)
{
	Object::Update(_dt);

	switch (currentState)
	{
	case STARTING:

		AddMovement(Vector2(0, speedY));

		if (transform->position.y >= RENDERER.GetSizeWindow().y)
		{
			currentState = StateShipBackground::WAITING;
		}

		break;
	case FINISHING:
		
		AddMovement(Vector2(0, speedY));

		break;
	case WAITING:

		rb->SetVeclocity(Vector2());
		transform->position.y = -transform->size.y; 

		if (isFinished)
		{
			currentState = FINISHING;
			SCORE.AddScore(5000); 
		}

		break; 
	default:
		break;
	}
}