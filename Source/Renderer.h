#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <cassert>
#include "Vector2.h"
#include "Transform.h"
#include "RenderManager.h"

class Renderer
{
protected:
	SDL_Texture* texture; 
	int surfaceW, surfaceH; 
	SDL_Rect sourceRect, destRect; 

	Transform* transform;
	SDL_RendererFlip flipMode; 

public:
	Renderer(Transform* transform);
	~Renderer();

	virtual void Render();
};

