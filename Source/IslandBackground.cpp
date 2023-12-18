#include "IslandBackground.h"

void IslandBackground::Movement()
{
	rb->SetVeclocity(Vector2(0, 16));
}

IslandBackground::IslandBackground(float posX, float posY)
{
	//TRANSFORM 
	transform = new Transform();
	transform->position = Vector2(posX, posY - RENDERER.GetSizeWindow().y);
	transform->angle = 0.0f;
	transform->scale = Vector2(1.0f, 1.0f);
	transform->size = Vector2(164, 124);
	transform->centered = false;

	//RENDER
	renderer = new ImageRenderer(transform, Vector2(22, 686), Vector2(16, 16));

	//RIGIDBODY
	rb = new RigidBody(transform);
}

void IslandBackground::Update(float dt)
{
	Object::Update(dt);

	Movement();

	Die();
}

void IslandBackground::Die()
{
	if (transform->position.y >= RENDERER.GetSizeWindow().y)
		Destroy();
}

