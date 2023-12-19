#pragma once
#include "PowerUp.h"

class GrayPowerUp : public PowerUp
{
public:
	GrayPowerUp(Player* p)
		:PowerUp(p)
	{
		// TRANSFORM
		transform = new Transform();
		transform->position = Vector2(RENDERER.GetSizeWindow().x * 0.5, RENDERER.GetSizeWindow().y * 0.5);
		transform->angle = 0.0f;
		transform->scale = Vector2(1.5f, 1.5f);
		transform->size = Vector2(16, 16);
		// RENDER
		renderer = new ImageRenderer(transform, Vector2(57, 140), Vector2(13, 10));
		// RIGID BODY 
		rb = new RigidBody(transform);
		Vector2 topLeft = transform->position - transform->size / 2;
		rb->AddCollision(new AABB(topLeft, transform->size));
		rb->SetLinearDrag(7);
	}
	virtual bool IsPlayer(Object* other) override
	{
		if (dynamic_cast<Player*>(other))
		{
			player->AddSupportPlanes();
			Destroy();
			return true;
		}
		return false;
	}
};