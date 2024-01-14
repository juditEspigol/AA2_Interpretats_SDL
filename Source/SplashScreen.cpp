#include "SplashScreen.h"

SplashScreen::SplashScreen()
{
	isFinished = false;
	timeToWait = 3.0f;
	timeWaiting = 0.0f;
	nextScene = MAIN;

	Transform* titleTransform = new Transform(
		RENDERER.GetSizeWindow() * 0.5,
		0.0f,
		Vector2(1, 1),
		Vector2(184, 48),
		true
	);

	objects.push_back(new GameObject(new ImageRenderer(titleTransform,
		Vector2(67, 704), Vector2(184, 48)), titleTransform));
}
void SplashScreen::OnEnter()
{
	RENDERER.SetWindowsColor(0, 0, 0);

	timeWaiting = 0.0f;
	objects[0]->SetScale(Vector2(1, 1));
}

void SplashScreen::Update(float dt)
{
	Scene::Update(dt); 

	timeWaiting += dt;
	objects[0]->SetScale(objects[0]->GetScale() + Vector2(0.01, 0.01));

	if (timeWaiting >= timeToWait)
		isFinished = true;
}