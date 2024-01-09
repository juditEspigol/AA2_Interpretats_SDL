#include "RenderManager.h"

void RenderManager::Init()
{
	try {
		InitSDL(); 
		CreateWindowAndRenderer(); 
		LoadGameTexture(); 
	}
	catch (std::exception& exception) {
		std::cout << exception.what(); 
		SDL_Quit(); 
		return; 
	}
}

void RenderManager::LoadGameTexture()
{
	// 1. Load a surface (.png -> .bitmap)
	SDL_Surface* surface = IMG_Load("Resources/1942WSea.png");
	assert(surface);

	// 2. From bitmap to texture (can be rendered on a rect)
	gameTexture = SDL_CreateTextureFromSurface(RENDERER.GetRenderer(), surface);
	assert(gameTexture);

	SDL_FreeSurface(surface);
}

void RenderManager::InitSDL()
{
	int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	if (result < 0) {
		throw SDL_GetError(); 
	}

	result = TTF_Init(); 
	if (result < 0)
		throw SDL_GetError(); 
}

void RenderManager::CreateWindowAndRenderer()
{
	int result = SDL_CreateWindowAndRenderer(
		sizeWindow.x, // x
		sizeWindow.y, // y 
		SDL_WINDOW_SHOWN, // type of screen
		&window, // REF window
		&renderer);// REF renderer

	if (result < 0) {
		throw SDL_GetError();
	}

	SDL_SetRenderDrawColor(renderer, 0, 95, 205, 212);
}


