#include "Renderer.h"


Renderer::Renderer(Transform* transform) 
	: transform(transform), flipMode(SDL_FLIP_NONE) {}

Renderer::~Renderer()
{
}

void Renderer::Render()
{
	SDL_Rect scaleDestRect = destRect;
	scaleDestRect.x = transform->position.x;
	scaleDestRect.y = transform->position.y;

	scaleDestRect.w *= transform->scale.x;
	scaleDestRect.h *= transform->scale.y;

	if (transform->centered)
	{
		scaleDestRect.x -= scaleDestRect.w / 2;
		scaleDestRect.y -= scaleDestRect.h / 2;
	}

	SDL_RenderCopyEx(
		RENDERER.GetRenderer(), texture,
		&sourceRect, &scaleDestRect,
		transform->angle,
		NULL,
		flipMode
	);
}