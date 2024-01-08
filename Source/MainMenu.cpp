#include "MainMenu.h"

MainMenu::MainMenu()
{
	/*objects.push_back( new Object("Resources/1942.png",
	Vector2(50,32),
	Vector2(5, 6),
	Vector2(25,16),
	RENDERER.GetRenderer())
);

objects[0]->GetRigidBody()->SetLinearDrag(5.0f);
objects[0]->SetPosition(Vector2(255, 255));


text = new TextRenderer(
	"guapo", 20, { 255, 0, 0 },
	new Transform(Vector2(256, 256), 0.0f, Vector2(1.0f, 1.0f), Vector2(250, 50), false),
	"Resources/PixelPowerline-11Mg.ttf",
	RENDERER.GetRenderer()
); */
	isFinished = false;
	nextScene = GAMEPLAY; 

	//0 -> Mouse Icone Radev  
	Transform* mouseTransform = new Transform(
		Vector2(),
		0.0f,
		Vector2(0.5, 0.5),
		Vector2(51, 79),
		true
	);
	objects.push_back(new GameObject(new ImageRenderer(mouseTransform,
		Vector2(0, 1121), Vector2(51, 79)), mouseTransform));
	//1 -> Button Play
	Transform* buttonPlayTransform = new Transform(
		RENDERER.GetSizeWindow() * 0.5,
		0.0f,
		Vector2(1, 1),
		Vector2(100, 20),
		true
	);
	objects.push_back(new GameObject(new ImageRenderer(buttonPlayTransform,
		Vector2(712, 783), Vector2(70, 11)), buttonPlayTransform));
	//2 -> Button Play
	/*objects.push_back(new Button(Vector2(100, 100), 
		new ImageRenderer(buttonPlayTransform, Vector2(712, 783), Vector2(70, 11)), buttonPlayTransform), 
		new TextObject("  ", 30, { 255, 255, 255 }, new Transform(RENDERER.GetSizeWindow() * 0.5, 0, Vector2(1, 1), Vector2(30, 30), true), "Resources/PixelPowerline-11Mg.ttf")
	);*/
}

void MainMenu::OnEnter()
{
	isFinished = false; 
}

void MainMenu::Update(float dt)
{
	Scene::Update(dt); 

	objects[0]->SetPosition(Vector2(IM.GetMouseX(), IM.GetMouseY()));

	if (objects[0]->GetRigidBody()->CheckCollision(objects[1]->GetRigidBody()))
	{
		objects[1]->SetScale(Vector2(3, 3));
	}
	else
	{
		objects[1]->SetScale(Vector2(1.5, 1.5));
	}
}