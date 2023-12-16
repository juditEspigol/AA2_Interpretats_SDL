#pragma once
#include <queue>
#include "Object.h"

#define SPAWNER Spawner::Instance()

class Spawner
{
private:
	std::queue<Object*> m_objectsToSpawn; 

	Spawner() = default;
	Spawner(const Spawner&) = delete;
	Spawner& operator =(const Spawner&) = delete;

public:
	inline static Spawner& Instance()
	{
		static Spawner manager;
		return manager;
	}

	inline void SpawnObject(Object* obj) { m_objectsToSpawn.push(obj); }
	bool HasObjectsToSpawn()
	{
		return m_objectsToSpawn.size() > 0;
	}
	bool HasUIToSpawn(); 
	Object* DequeueObjectToSpawn()
	{
		Object* objToSpawn = m_objectsToSpawn.front();
		m_objectsToSpawn.pop();
		return objToSpawn;
	}

	Object* DequeueUIToSpawn(); 
	void ClearSpawnQueue()
	{
		while(!m_objectsToSpawn.empty())
			m_objectsToSpawn.pop();
	}
};

