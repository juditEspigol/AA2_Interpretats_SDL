#pragma once
#include "Object.h"
#include "ImageRenderer.h"

class GameObject : public Object
{
protected: 
	ImageRenderer* renderer; 

	std::unordered_map<std::string, ImageRenderer*> renderers; 

public: 
	GameObject() = default;
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