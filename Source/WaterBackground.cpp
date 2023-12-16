#include "WaterBackground.h"

void WaterBackGround::Movement()
{
	rb->SetVeclocity(Vector2(0, 106));
}

WaterBackGround::WaterBackGround(float _offset)
{
	posToRestart = RENDERER.GetSizeWindow().x;

	//TRANSFORM
	transform.position = Vector2(0,0 - _offset);
	transform.angle = 0.0f;
	transform.scale = Vector2(1.0f, 1.0f);
	transform.size = Vector2(RENDERER.GetSizeWindow().x, RENDERER.GetSizeWindow().y + 1);
	transform.centered = false;

	//RENDER
	renderer = new ImageRenderer(&transform, Vector2(22, 646), Vector2(16, 16));

	//RIGIDBODY
	rb = new RigidBody(&transform);
}

void WaterBackGround::Update(float dt)
{
	Object::Update(dt);

	Movement();

	if (transform.position.y >= RENDERER.GetSizeWindow().y)
	{
		ScrollFinished();
	}
}

void WaterBackGround::ScrollFinished()
{
	transform.position = Vector2(0, 0 - posToRestart);
}