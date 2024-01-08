#pragma once
#include "GameObject.h"
#include "TextObject.h"

class Button : public GameObject
{
private:
	TextObject* text; 
public:
	Button(Vector2 position, ImageRenderer* image, TextObject* text)
	{
		Transform* t = new Transform(
			position,
			0.0f,
			Vector2(1.5, 1.5),
			Vector2(100, 20),
			true
		);
		
		isPendingDestroy = false;
		transform = t;
		renderer = image; 
		this->text = text; 

		rb = new RigidBody(t);
		Vector2 topLeft = transform->position - transform->size / 2;
		rb->AddCollision(new AABB(topLeft, transform->size));
	}
};