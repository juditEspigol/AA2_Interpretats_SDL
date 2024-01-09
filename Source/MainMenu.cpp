#include "MainMenu.h"

MainMenu::MainMenu()
{
	isFinished = false;
	nextScene = GAMEPLAY; 
	enableAudio = true; 

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
	objects.push_back(new Button(Vector2(RENDERER.GetSizeWindow().x * 0.5, 100), "PLAY GAME"));
	objects.push_back(new Button(Vector2(RENDERER.GetSizeWindow().x * 0.5, 200), "RANKING"));
	objects.push_back(new Button(Vector2(RENDERER.GetSizeWindow().x * 0.5, 300), "ENABLED AUDIO"));
	objects.push_back(new Button(Vector2(RENDERER.GetSizeWindow().x * 0.5, 400), "EXIT"));
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
		nextScene = RANKING;
		isFinished = true;
	}
	else if (dynamic_cast<Button*>(objects[2])->GetActivated()) // audio
	{
		if (enableAudio)
		{
			dynamic_cast<Button*>(objects[2])->GetText()->GetRenderer()->NewText("DISABLE AUDIO"); 
			AUDIO.Mute();
			enableAudio = false; 
		}
		else
		{
			dynamic_cast<Button*>(objects[2])->GetText()->GetRenderer()->NewText("ENABLE AUDIO");
			AUDIO.Unmute();
			enableAudio = true;
		}
	}
	else if (dynamic_cast<Button*>(objects[3])->GetActivated()) // exit
	{
		IM.ExitGame(); 
	}

	
}