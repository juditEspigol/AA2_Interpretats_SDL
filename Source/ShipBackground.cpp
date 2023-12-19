#include "ShipBackground.h"

void ShipBackGround::Movement()
{
	rb->SetVeclocity(Vector2(0, speed));
}

ShipBackGround::ShipBackGround()
{
	speed = -16;

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

void ShipBackGround::Update(float dt)
{
	Object::Update(dt);
	Movement();

	if (transform->position.y <= 320)
	{
		speed = 0;
	}
}

void ShipBackGround::StopMoving()
{
	if (transform->position.y >= RENDERER.GetSizeWindow().y + 5)
	{
		rb->SetVeclocity(Vector2());
	}
}
