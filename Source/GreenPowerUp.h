#pragma once
#include "PowerUp.h"
#include "Player.h"

class GreenPowerUp : public PowerUp
{
protected:

public:
	GreenPowerUp()
	{
		// TRANSFORM
		transform.position = Vector2(RENDERER.GetSizeWindow().x * 0.5, RENDERER.GetSizeWindow().y * 0.5);
		transform.angle = 0.0f;
		transform.scale = Vector2(1.5f, 1.5f);
		transform.size = Vector2(16, 16);
		// RENDER
		renderer = new ImageRenderer(&transform, Vector2(74, 140), Vector2(13, 10));
		// RIGID BODY 
		rb = new RigidBody(&transform);
		Vector2 topLeft = transform.position - transform.size / 2;
		rb->AddCollision(new AABB(topLeft, transform.size));
		rb->SetLinearDrag(7);
	}
	virtual void Update(float dt) override
	{
		GameObject::Update(dt);
	}
	virtual void OnCollisionEnter(Object* other) override
	{
		if (rb->CheckCollision(other->GetRigidBody()))
		{
			if (IsPlayer(other))
				return;
		}
	}

	bool IsPlayer(Object* other)
	{
		if (dynamic_cast<Player*>(other))
		{
			return true;
		}/*
		SupportPlane* support = new SupportPlane(Vector2(other->GetSize().x * 2, 0), other->GetPosition());
		SPAWNER.SpawnObject(support);
		supportPlanes.push_back(support);

		SupportPlane* support2 = new SupportPlane(Vector2(-(transform.size.x * 2), 0), transform.position);
		SPAWNER.SpawnObject(support2);
		supportPlanes.push_back(support2);*/
	}
};