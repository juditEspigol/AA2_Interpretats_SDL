#pragma once
#include <unordered_map>
#include <string>
#include "Scene.h"

#define SCENE_M SceneManager::Instance()

class SceneManager
{
private:
	std::unordered_map<std::string, Scene*> scenes; 
	Scene* currentScene = nullptr; 

	SceneManager() = default;
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator =(const SceneManager&) = delete;

public:
	inline static SceneManager& Instance()
	{
		static SceneManager manager;
		return manager;
	}
	inline bool AddScene(std::string name, Scene* s)
	{
		if (scenes.find(name) == scenes.end())
		{
			scenes.emplace(name, s);
			return true;
		}

		return false;
	}
	inline Scene* GetScene(std::string name)
	{ 
		if (scenes.find(name) != scenes.end())
			return scenes[name];

		return nullptr;
	}
	inline Scene* GetCurrentScene() { return currentScene; }
	inline bool SetCurrentScene(std::string name) 
	{ 
		if (scenes.find(name) != scenes.end())
		{
			currentScene = scenes[name];
			return true;
		}
		return false;
	}
};

