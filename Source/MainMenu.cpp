#include "MainMenu.h"

MainMenu::MainMenu()
{
	isFinished = false;
	nextScene = GAMEPLAY; 

	//0 -> Mouse Icone Radev  
	/*Transform* mouseTransform = new Transform(
		Vector2(),
		0.0f,
		Vector2(0.5, 0.5),
		Vector2(51, 79),
		true
	);
	objects.push_back(new GameObject(new ImageRenderer(mouseTransform,
		Vector2(0, 1121), Vector2(51, 79)), mouseTransform));*/
	//1 -> Button Play
	objects.push_back(new Button(Vector2(RENDERER.GetSizeWindow().x * 0.5, 100), "Play Game"));
	objects.push_back(new Button(Vector2(RENDERER.GetSizeWindow().x * 0.5, 200), "Ranking"));
	objects.push_back(new Button(Vector2(RENDERER.GetSizeWindow().x * 0.5, 300), "Audio"));
	objects.push_back(new Button(Vector2(RENDERER.GetSizeWindow().x * 0.5, 400), "Exit"));
}

void MainMenu::OnEnter()
{
	isFinished = false; 
}

void MainMenu::Update(float dt)
{
	Scene::Update(dt); 

	if (dynamic_cast<Button*>(objects[0])->GetActivated()) // play game
	{
		nextScene = GAMEPLAY; 
		isFinished = true; 
	}
	else if (dynamic_cast<Button*>(objects[1])->GetActivated()) // ranking
	{
		std::cout << "RANKING" << std::endl; 
		/*nextScene = RANKING;
		isFinished = true;*/
	}
	else if (dynamic_cast<Button*>(objects[2])->GetActivated()) // audio
	{
		std::cout << "AUDIO" << std::endl;
	}
	else if (dynamic_cast<Button*>(objects[3])->GetActivated()) // exit
	{
		IM.ExitGame(); 
	}

	
}