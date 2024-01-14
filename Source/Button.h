#pragma once
#include "GameObject.h"

#include "TextObject.h"

class Button : public GameObject
{
private:
	bool activated; 
	bool pressed; 
	bool isHovered;
	bool hoverHasSounded;
	TextObject* textButton; 

	//Audio
	int onHoverClip;
	int onClickClip;

public:
	Button(Vector2 position, std::string text, Vector2 size = Vector2(200, 40))
	{
		isPendingDestroy = false; 
		activated = false;
		pressed = false; 
		isHovered = false;
		hoverHasSounded = false;

		onHoverClip = AUDIO.LoadClip("Resources/Audio/onHoverClip.mp3");
		onClickClip = AUDIO.LoadClip("Resources/Audio/onClickClip.mp3");

		// TRANSFORM 
		transform = new Transform();
		transform->position = position;
		transform->angle = 0.0f;
		transform->scale = Vector2(1.5f, 1.5f);
		transform->size = size;

		textButton = new TextObject(text, 12, {255, 255, 255}, transform, "Resources/PixelPowerline-11Mg.ttf");

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
			isHovered = true;

			if (isHovered && !hoverHasSounded)
			{
				AUDIO.PlayClip(onHoverClip);
				hoverHasSounded = true;
			}

			this->SetScale(Vector2(1.8, 1.8)); 

			int mouseX = IM.GetMouseX(); 
			int mouseY = IM.GetMouseY(); 

			if (SDL_GetMouseState(&mouseX, &mouseY) == SDL_BUTTON_LEFT && !activated && !pressed) 
			{
				AUDIO.PlayClip(onClickClip);
				pressed = true; 
				activated = true;
			}
			else
			{
				activated = false;
			}
			
			return true; 
		}

		isHovered = false;
		hoverHasSounded = false;

		this->SetScale(Vector2(1.5, 1.5));
		pressed = false; 
		activated = false; 
		return false; 
	}

	inline bool GetActivated() const { return activated; }

	inline TextObject* GetText() const { return textButton; }
};