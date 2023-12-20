#pragma once
#include "Renderer.h"

class ImageRenderer : public Renderer
{
public:
	ImageRenderer(Transform* transform, Vector2 sourceOffset, Vector2 sourceSize, SDL_RendererFlip flipMode = SDL_FLIP_NONE);

	virtual void Reset() {}; 

	virtual void Update(float dt) {}

	virtual bool LastFrame() { return false; }
};