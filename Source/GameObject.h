#pragma once
#include "Object.h"

#include "RenderManager.h"
#include "ImageRenderer.h"
#include "AnimatedImageRenderer.h"

class GameObject : public Object
{
protected: 
	ImageRenderer* renderer; 

	std::unordered_map<std::string, ImageRenderer*> renderers; 

public: 
	GameObject() = default;
	GameObject(ImageRenderer* image, Transform* t)
		: renderer(image) 
	{
		isPendingDestroy = false; 
		transform = t; 

		rb = new RigidBody(t); 
		Vector2 topLeft = transform->position - transform->size / 2;
		rb->AddCollision(new AABB(topLeft, transform->size));
	};
	~GameObject()
	{
		delete renderer;
	}

	virtual void Update(float dt) override
	{
		rb->Update(dt);
		renderer->Update(dt); 
	};
	virtual void Render()
	{
		renderer->Render();
	}

	virtual void OnCollisionEnter(Object* other) override
	{

	}
	void ChangeAnimation(std::string animID)
	{
		if (renderers[animID] == renderer)
			return; 

		renderers[animID]->Reset(); 
		renderer = renderers[animID]; 
	}
};