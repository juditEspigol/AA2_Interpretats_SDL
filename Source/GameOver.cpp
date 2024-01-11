#include "GameOver.h"

GameOver::GameOver()
{
	isFinished = false; 
	nextScene = MAIN; 

	//0 -> Button!!! Don't move
	objects.push_back(new Button(Vector2(RENDERER.GetSizeWindow().x * 0.5, RENDERER.GetSizeWindow().y * 0.85), "BACK TO MAIN", Vector2(180, 40)));
}

void GameOver::OnEnter()
{
	RENDERER.SetWindowsColor(0, 0, 0);
}

void GameOver::Update(float dt)
{
	Scene::Update(dt); 

	if (dynamic_cast<Button*>(objects[0])->GetActivated()) 
	{
		isFinished = true;
	}
}
