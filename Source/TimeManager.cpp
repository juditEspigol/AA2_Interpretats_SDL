#include "TimeManager.h"

TimeManager::TimeManager() 
{
    previousGameTime = (double)SDL_GetTicks() / 1000.0;

    deltaTime = 0.0f;
    FPS = 60;
    frameTime = 1.0f / (float)FPS;
}

void TimeManager::Update()
{
    float gameTime = (double)SDL_GetTicks() / 1000.0;

    deltaTime += gameTime - previousGameTime;
    previousGameTime = gameTime;
}
