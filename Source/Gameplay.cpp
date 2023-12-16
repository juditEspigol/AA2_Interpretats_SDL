#include "Gameplay.h"

Gameplay::Gameplay()
{
	objects.push_back(new Player());  

	sfxID = AUDIO.LoadClip("Resources/Audio/discord-notification.mp3");

	nextScene = MAIN;
}

void Gameplay::OnEnter()
{
}

void Gameplay::Render()
{
	Scene::Render(); 
}

void Gameplay::Update(float dt)
{
	Scene::Update(dt); 

	isFinished = IM.CheckKeyState(SDLK_e, PRESSED);
}
