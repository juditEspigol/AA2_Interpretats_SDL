#pragma once
#include <SDL_mixer.h>
#include <unordered_map>
#include <queue>
#include <string>

#define AUDIO AudioManager::Instance()

class AudioManager
{
private:
	const int maxChannels = 128;
	std::unordered_map<int, Mix_Chunk*> clips; 
	std::unordered_map<int, Mix_Music*> songs; 

	bool muted; 
	std::queue<int> avaliableIDs; 

	AudioManager();
	~AudioManager(); 
	AudioManager(const AudioManager&) = delete;
	AudioManager& operator =(const AudioManager&) = delete;

public:
	inline static AudioManager& Instance()
	{
		static AudioManager manager;
		return manager;
	}

	int LoadClip(std::string path); 
	int LoadMusic(std::string path); 

	void PlayClip(int ID); 
	void StopClip(int ID); 
	void PlayMusic(int ID); 
	void StopMusic(int ID); 

	void FreeClip(int ID); 
	void FreeMusic(int ID); 

	void Mute();
	void Unmute();
	inline bool GetMuted() { return muted; }
};