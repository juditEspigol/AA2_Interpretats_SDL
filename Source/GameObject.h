#pragma once
#include "Object.h"
#include "ImageRenderer.h"

class GameObject : public Object
{
protected: 
	ImageRenderer* renderer; 

public: 
	GameObject() = default;
	~GameObject()
	{
		delete renderer;
	}

	virtual void Update(float dt) 
	{
		rb->Update(dt); 
	};
	virtual void Render()
	{
		renderer->Render();
	}

	virtual void OnCollisionEnter(Object* other) override
	{

	}
};