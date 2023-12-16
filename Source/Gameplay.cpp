#include "Gameplay.h"

Gameplay::Gameplay()
{
	objects.push_back(new Player());  
	objects.push_back(new SmallNormalPlane());
	objects.push_back(new SmallRedPlane());
	objects.push_back(new MediumYellowPlane());
	objects.push_back(new BigGreenPlane());

	sfxID = AUDIO.LoadClip("Resources/Audio/discord-notification.mp3");
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
}
