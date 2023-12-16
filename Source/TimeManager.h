#pragma once
#include <SDL.h>

#define TIME TimeManager::Instance()

class TimeManager
{
private: 

	float deltaTime; 
	int FPS; 
	float frameTime; 
	float previousGameTime;

	TimeManager();
	TimeManager(const TimeManager&) = delete;
	TimeManager& operator =(const TimeManager&) = delete;

public:

	inline static TimeManager& Instance()
	{
		static TimeManager manager;
		return manager;
	}

	void Update(); 

	inline bool ShouldUpdateGame() { return deltaTime > frameTime; }
	inline void ResetDeltaTime() { deltaTime = 0.0f; }

	inline float GetDeltaTime() const { return deltaTime; }
	inline void SetFPS(int _FPS) { FPS = _FPS; }
};