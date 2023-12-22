#include "PowerUp.h"


PowerUp::PowerUp(Player* p)
	: player(p), speed(10)
{
	// TRANSFORM
	transform = new Transform();
	transform->size = Vector2(16, 16);
	int randomPosX = transform->size.x + rand() % ((int)RENDERER.GetSizeWindow().x - (int)transform->size.x);
	transform->position = Vector2(randomPosX, 0);
	transform->angle = 0.0f;
	transform->scale = Vector2(1.5f, 1.5f);
	transform->size = Vector2(16, 16);

	// RIGID BODY 
	rb = new RigidBody(transform);
	Vector2 topLeft = transform->position - transform->size / 2;
	rb->AddCollision(new AABB(topLeft, transform->size));
	rb->SetLinearDrag(7);
}

void PowerUp::Update(float dt)
{
	GameObject::Update(dt);

	AddMovement(); 
}

void PowerUp::AddMovement()
{
	Vector2 force = Vector2();

	force.y += 1;

	force.Normalize();
	force = force * speed;
	rb->AddForce(force);
}

void PowerUp::GiveScore()
{
	SCORE.AddScore(scoreToGive);
}

void PowerUp::OnCollisionEnter(Object* other)
{
	if (rb->CheckCollision(other->GetRigidBody()))
	{
		if (IsPlayer(other))
			
		if (IsOutOfWindow())
			return;
	}
}

bool PowerUp::IsOutOfWindow()
{
	if (transform->position.y > RENDERER.GetSizeWindow().y + transform->size.y
		|| transform->position.y < -transform->size.y
		|| transform->position.x < -transform->size.x
		|| transform->position.x > RENDERER.GetSizeWindow().x + transform->size.x)
	{
		Destroy();
		return true;
	}
	return false;
}