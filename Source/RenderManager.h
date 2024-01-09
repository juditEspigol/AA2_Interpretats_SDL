#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <cassert>
#include <exception>
#include <iostream>

#include "Vector2.h"

#define RENDERER RenderManager::Instance()

class RenderManager // render manager
{
private:

	SDL_Texture* gameTexture; 
	SDL_Window* window;
	SDL_Renderer* renderer;

	Vector2 sizeWindow = Vector2(512, 512); 

	RenderManager() = default;
	RenderManager(const RenderManager&) = delete;
	RenderManager& operator =(const RenderManager&) = delete;

	void InitSDL();
	void CreateWindowAndRenderer();

public:
	inline static RenderManager& Instance()
	{
		static RenderManager manager;
		return manager;
	}

	void Init();
	void LoadGameTexture(); 
	SDL_Renderer* GetRenderer() { return renderer; }
	SDL_Texture* GetGameTexture() { return gameTexture; }
	Vector2 GetSizeWindow() { return sizeWindow; }
	void SetWindowsColor(int red, int green, int blue, int h = 212) { SDL_SetRenderDrawColor(renderer, red, green, blue, h); }
};