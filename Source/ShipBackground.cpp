#include "ShipBackground.h"

void ShipBackGround::Movement()
{
	rb->SetVeclocity(Vector2(0, -32));
}

ShipBackGround::ShipBackGround()
{
	//TRANSFORM
	transform = new Transform();
	transform->position = Vector2(RENDERER.GetSizeWindow().x * 0.5, RENDERER.GetSizeWindow().y - 10);
	transform->angle = 0.0f;
	transform->scale = Vector2(1.0f, 1.0f);
	transform->size = Vector2(22*10, 120*10);
	transform->centered = false;

	//RENDER
	renderer = new ImageRenderer(transform, Vector2(669, 734), Vector2(22, 120), SDL_FLIP_VERTICAL);

	//RIGIDBODY
	rb = new RigidBody(transform);
}

void ShipBackGround::Update(float dt)
{
	Object::Update(dt);
	Movement();
}

void ShipBackGround::StopMoving()
{
	if (transform->position.y >= RENDERER.GetSizeWindow().y + 5)
	{
		rb->SetVeclocity(Vector2());
	}
}
