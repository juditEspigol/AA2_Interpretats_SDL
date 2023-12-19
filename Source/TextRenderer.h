#pragma once
#include <SDL_ttf.h>
#include "Renderer.h"

class TextRenderer : public Renderer
{
protected:
	std::string fontPath;
	TTF_Font* font;
	std::string text;
	int fontSize; 
	SDL_Color color; 

public:
	TextRenderer(std::string text, int fontSize, SDL_Color color, Transform* transform, std::string resourcePath, SDL_RendererFlip flipMode = SDL_FLIP_NONE);
	~TextRenderer()
	{
		SDL_DestroyTexture(texture);
	}
	void SetText(std::string text, int fontSize = 0, SDL_Color color = {0, 0, 0});
	inline void NewText(const std::string text) { SetText(text, fontSize, color); }
};