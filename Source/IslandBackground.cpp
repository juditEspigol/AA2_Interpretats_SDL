#include "IslandBackground.h"

void IslandBackground::Movement()
{
	rb->SetVeclocity(Vector2(0, 106));
}

IslandBackground::IslandBackground(Vector2 pos)
{
	//TRANSFORM 
	transform.position = pos;
	transform.angle = 0.0f;
	transform.scale = Vector2(1.0f, 1.0f);
	transform.size = Vector2(64, 64);
	transform.centered = false;

	//RENDER
	renderer = new ImageRenderer(&transform, Vector2(22, 686), Vector2(16, 16));

	//RIGIDBODY
	rb = new RigidBody(&transform);
}

void IslandBackground::Update(float dt)
{
	Object::Update(dt);
	Movement();
}
