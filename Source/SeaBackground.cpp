#include "SeaBackground.h"

void SeaBackground::Movement()
{
	rb->SetVeclocity(Vector2(0, 16));
}

SeaBackground::SeaBackground(float offset)
{

	posToRestart = RENDERER.GetSizeWindow().x;

	//TRANSFORM
	transform = new Transform();
	transform->position = Vector2(0, 0 - offset);
	transform->angle = 0.0f;
	transform->scale = Vector2(1.0f, 1.0f);
	transform->size = Vector2(512, 512);
	transform->centered = false;

	//RENDER
	renderer = new ImageRenderer(transform, Vector2(327, 0), Vector2(512, 512));

	//RIGIDBODY
	rb = new RigidBody(transform);
}

void SeaBackground::Update(float dt)
{
	Object::Update(dt);

	Movement();

	if (transform->position.y >= RENDERER.GetSizeWindow().y)
	{
		ScrollFinished();
	}
}

void SeaBackground::ScrollFinished()
{
	transform->position = Vector2(0, 1 - posToRestart);
}
