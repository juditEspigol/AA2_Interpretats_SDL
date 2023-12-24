#include "TextRenderer.h"

TextRenderer::TextRenderer(std::string text, int fontSize, SDL_Color color, Transform* transform, std::string resourcePath, SDL_RendererFlip flipMode)
	: Renderer(transform, flipMode), text(text), fontSize(fontSize), color(color)
{
	fontPath = resourcePath;
	SetText(text, fontSize, color);
}

void TextRenderer::SetText(std::string text, int fontSize, SDL_Color color)
{
	if (texture != nullptr)
		SDL_DestroyTexture(texture);

	this->text = text;
	this->color = color;
	this->fontSize = fontSize;

	// 1. Load a font
	font = TTF_OpenFont(fontPath.c_str(), fontSize);
	assert(font);

	// 2. Load a surface (.png -> .bitmap)
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	assert(surface);

	// 3. From bitmap to texture (can be rendered on a rect)
	texture = SDL_CreateTextureFromSurface(RENDERER.GetRenderer(), surface);
	assert(texture);

	surfaceW = surface->w;
	surfaceH = surface->h;

	SDL_FreeSurface(surface);
	TTF_CloseFont(font);

	// 4. Set the source rect
	sourceRect = {
		0, 0,
		surfaceW, surfaceH 
	};
	destRect = SDL_Rect{
		(int)transform->position.x, (int)transform->position.y,
		(int)(fontSize * text.length()), (int)(fontSize * 1.5f)
	};
}
