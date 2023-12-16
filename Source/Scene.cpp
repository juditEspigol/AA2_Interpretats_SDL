#include "Scene.h"

std::string Scene::OnExit()
{
	isFinished = false;
	return nextScene; 
}

void Scene::Update(float dt)
{
	// Destroying
	for (int i = objects.size() - 1; i >= 0; i--)
	{
		if (objects[i]->IsPendingDestroy())
		{
 			delete objects[i]; 
			objects.erase(objects.begin() + i); 
		}
	}
	for (int i = ui.size() - 1; i >= 0; i--)
	{
		if (ui[i]->IsPendingDestroy())
		{
			delete ui[i];
			ui.erase(ui.begin() + i);
		}
	}
	// Spawning
	while (SPAWNER.HasObjectsToSpawn())
		objects.push_back(SPAWNER.DequeueObjectToSpawn());
	
	for (Object* object : objects)
	{
		object->Update(dt);

		// Detect Collisions
		for (Object* other : objects)
			object->OnCollisionEnter(other);
		
	}
	for (Object* gameUI : ui)
		gameUI->Update(dt);
}

void Scene::Render()
{
	for (Object* o : objects)
		o->Render();

	for (Object* gameUI : ui)
		gameUI->Render();

}
