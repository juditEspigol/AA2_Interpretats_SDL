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
	//0, 1, 2, 3 -> Buttons!!! Don't move
	objects.push_back(new Button(Vector2(RENDERER.GetSizeWindow().x * 0.5, 115), "PLAY GAME"));
	objects.push_back(new Button(Vector2(RENDERER.GetSizeWindow().x * 0.5, 200), "RANKING"));
	objects.push_back(new Button(Vector2(RENDERER.GetSizeWindow().x * 0.5, 285), "DISABLE AUDIO"));
	objects.push_back(new Button(Vector2(RENDERER.GetSizeWindow().x * 0.5, 370), "EXIT"));
}

void MainMenu::OnEnter()
{
	RENDERER.SetWindowsColor(0, 0, 0);
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
			dynamic_cast<Button*>(objects[2])->GetText()->GetRenderer()->NewText("ENABLE AUDIO"); 
			AUDIO.Mute();
			enableAudio = false; 
		}
		else
		{
			dynamic_cast<Button*>(objects[2])->GetText()->GetRenderer()->NewText("DISABLE AUDIO");
			AUDIO.Unmute();
			enableAudio = true;
		}
	}
	else if (dynamic_cast<Button*>(objects[3])->GetActivated()) // exit
	{
		IM.ExitGame(); 
	}

	
}