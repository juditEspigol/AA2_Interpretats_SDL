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
	nextScene = GAMEPLAY; 
}

void MainMenu::OnEnter()
{
}

void MainMenu::Update(float dt)
{
	Scene::Update(dt); 

	if (IM.CheckKeyState(SDLK_e, PRESSED))
		isFinished = true;

	/*
	objects[1]->SetPosition(Vector2(IM.GetMouseX(), IM.GetMouseY()));
	//gameTime += dt; 
	//objects[0]->SetPosition(Vector2(256 + cos(gameTime * 3.1416 * 2.0) * 100, 256 + sin(gameTime * 3.1416 * 2.0) * 100));

	if (objects[0]->GetRigidBody()->CheckCollision(objects[1]->GetRigidBody()))
	{
		objects[0]->SetRotation(objects[0]->GetRotation() + 180.0f * dt); 
		objects[0]->SetScale(Vector2(2,2)); 
	}
	else
	{
		objects[0]->SetScale(Vector2(1, 1));
	}
	*/

	//Vector2 inputForce = Vector2(); 

	////VERTICAL
	//if (IM.CheckKeyState(SDLK_w, HOLD))
	//	inputForce.y -= 1;
	//if (IM.CheckKeyState(SDLK_s, HOLD))
	//	inputForce.y += 1;
	////HORIZONTAL
	//if (IM.CheckKeyState(SDLK_a, HOLD))
	//	inputForce.x -= 1;
	//if (IM.CheckKeyState(SDLK_d, HOLD))
	//	inputForce.x += 1;

	//inputForce.Normalize();
	//inputForce = inputForce * 50; 
	//objects[0]->GetRigidBody()->AddForce(inputForce);

	//Vector2 knockback = Vector2();
	////VERTICAL
	//if (objects[0]->GetPosition().y <= 20.0f)
	//	knockback.y += 1;
	//if (objects[0]->GetPosition().y >= 500.0)
	//	knockback.y -= 1;
	//if (objects[0]->GetPosition().x <= 20.0f)
	//	knockback.x += 1;
	//if (objects[0]->GetPosition().x >= 500.0)
	//	knockback.x -= 1;

	//knockback.Normalize();
	//knockback = knockback * 100;
	//objects[0]->GetRigidBody()->AddForce(knockback);


	//if (IM.CheckKeyState(SDLK_t, HOLD))
	//	text->SetText("muacky", RENDERER.GetRenderer());
}