#include "SupportPlane.h"

// OnCollisionEnter
#include "EnemyBullet.h"
#include "EnemyPlane.h"

SupportPlane::SupportPlane(bool right, Vector2 pos)
	: isRight(right), isLocated(false)
{
	isPendingDestroy = false;

	// TRANSFORM
	transform = new Transform();
	transform->size = Vector2(16, 16);

	offset = Vector2(transform->size.x * 2, 0);
	if (!right)
		offset = offset * -1;

	transform->position = Vector2(pos.x - offset.x, 0);
	transform->angle = 0.0f;
	transform->scale = Vector2(1.5f, 1.5f);

	// RENDER
	CreateAnimations(); 
	renderer = renderers["Idle"];

	// RIGID BODY 
	rb = new RigidBody(transform);
	Vector2 topLeft = transform->position - transform->size / 2;
	rb->AddCollision(new AABB(topLeft, transform->size));
	rb->SetLinearDrag(7);
}

void SupportPlane::Update(float dt)
{
	GameObject::Update(dt); 
}
void SupportPlane::LocatePlane(Vector2 playerPosition, float dt)
{
	Vector2 positionToGo = playerPosition - offset;

	if (isLocated)
	{
		transform->position = positionToGo;
	}
	else
	{
		Vector2 direction = positionToGo - transform->position;

		if (direction.Magnitude() <= 10)
		{
			isLocated = true;
			SetRotation(0);
		}
		else
		{
			Vector2 force = Vector2();

			//SPINNING
			SetRotation(GetRotation() + (360 * dt));
			//VERTICAL
			if (transform->position.y < positionToGo.y) // support up, player down
				force.y += 1;
			if (transform->position.y > positionToGo.y) // support down, player up
				force.y -= 1;
			//HORITZONTAL
			if (transform->position.x < positionToGo.x) // support left, player right
				force.x += 1;
			if (transform->position.x > positionToGo.x) // support right, player left
				force.x -= 1;

			force.Normalize();
			force = force * 70;
			rb->AddForce(force);
		}
	}
}

void SupportPlane::OnCollisionEnter(Object* other)
{
	if (!isLocated)
		return; 

	if (rb->CheckCollision(other->GetRigidBody()))
	{
		if (IsEnemyPlane(other))
			return;
		if (IsEnemyBullet(other))
			return;
	}
}
bool SupportPlane::IsEnemyPlane(Object* other)
{
	if (dynamic_cast<EnemyPlane*>(other))
	{
		Destroy();
		return true;
	}

	return false;
}
bool SupportPlane::IsEnemyBullet(Object* other)
{
	if (dynamic_cast<EnemyBullet*>(other))
	{
		Destroy();
		return true;
	}
	return false;
}

void SupportPlane::Shoot()
{
	if(isLocated)
		SPAWNER.SpawnObject(new PlayerBullet(transform->position));
}

void SupportPlane::CreateAnimations()
{
	//IDLE 
	renderers.emplace("Idle", new ImageRenderer(transform, Vector2(49, 83), Vector2(18, 12)));

	// RIGHT & LEFT
	std::vector<Vector2> deltas{ Vector2(0, 0) };
	renderers.emplace("Right", new AnimatedImageRenderer(transform, Vector2(9, 83), Vector2(18, 12), deltas, false, 20));
	renderers.emplace("Left", new AnimatedImageRenderer(transform, Vector2(9, 83), Vector2(18, 12), deltas, false, 20, SDL_FLIP_HORIZONTAL));
}