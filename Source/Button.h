#pragma once
#include "GameObject.h"

#include "TextObject.h"

class Button : public GameObject
{
private:
	bool activated; 
	TextObject* textButton; 

public:
	Button(Vector2 position, std::string text, SDL_Color color = {255, 255, 255})
	{
		isPendingDestroy = false; 
		activated = false;

		// TRANSFORM 
		transform = new Transform();
		transform->position = position;
		transform->angle = 0.0f;
		transform->scale = Vector2(1.5f, 1.5f);
		transform->size = Vector2(100, 25);

		textButton = new TextObject(text, 10, color, transform, "Resources/PixelPowerline-11Mg.ttf");

		// RENDER
		renderers.emplace("Idle", new ImageRenderer(transform, Vector2(6, 625), Vector2(62, 13))); 
		renderer = renderers["Idle"]; 

		// RIGID BODY
		rb = new RigidBody(transform);
		Vector2 topLeft = transform->position - transform->size / 2;
		rb->AddCollision(new AABB(topLeft, transform->size));
	}
	virtual void Render() override
	{
		GameObject::Render(); 
		textButton->Render(); 
	}

	virtual void OnCollisionEnter(Object* other)
	{
		if (dynamic_cast<TextObject*>(other))
			return;

		if (rb->CheckCollision(other->GetRigidBody()))
		{
			if (IsMouse(other))
				return; 
		}
	}

	bool IsMouse(Object* other)
	{
		if (rb->CheckOverlappingPoint(Vector2(IM.GetMouseX(), IM.GetMouseY())))
		{
			this->SetScale(Vector2(1.8, 1.8)); 

			int mouseX = IM.GetMouseX(); 
			int mouseY = IM.GetMouseY(); 

			if (SDL_GetMouseState(&mouseX, &mouseY) == SDL_BUTTON_LEFT && activated == false)
				activated = true;
			else
				activated = false; 
			
			return true; 
		}

		this->SetScale(Vector2(1.5, 1.5));
		activated = false;
		return false; 
	}

	inline bool GetActivated() const { return activated; }
};