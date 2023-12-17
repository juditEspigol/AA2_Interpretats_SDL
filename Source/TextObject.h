#pragma once
#include "Object.h"
#include "TextRenderer.h"

class TextObject : public Object
{
protected: 
	TextRenderer* renderer; 

public:
	TextObject(std::string text, int fontSize, SDL_Color color, Transform* transform, std::string resourcePath)
	{
		renderer = new TextRenderer(text, fontSize, color, transform, resourcePath); 
	}
	virtual ~TextObject()
	{
		delete renderer; 
	}

	virtual void Update(float dt)
	{}
	virtual void Render()
	{
		renderer->Render(); 
	}
	TextRenderer* GetRenderer() { return renderer; }
};