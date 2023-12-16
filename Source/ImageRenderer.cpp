#include "ImageRenderer.h"

ImageRenderer::ImageRenderer(Transform* transform, Vector2 sourceOffset, Vector2 sourceSize)
	: Renderer(transform)	
{
	sourceRect = SDL_Rect{
		(int)sourceOffset.x, (int)sourceOffset.y,
		(int)sourceSize.x, (int)sourceSize.y };
	destRect = SDL_Rect{
		(int)transform->position.x, (int)transform->position.y,
		(int)transform->size.x, (int)transform->size.y };

	texture = RENDERER.GetGameTexture();
}