#include "AudioManager.h"
#include <cassert>

AudioManager::AudioManager()
    : muted(false) 
{
    assert(!Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048));
    Mix_AllocateChannels(maxChannels); 
    for (int i = 0; i < maxChannels; i++)
        avaliableIDs.push(i);
}

AudioManager::~AudioManager()
{
    // Netejar els chunks
    for (std::pair<const int, Mix_Chunk*> kv : clips)
        Mix_FreeChunk(kv.second); 
    
    clips.clear(); 
    // Netejar els songs
    for (std::pair<const int, Mix_Music*> kv : songs)
        Mix_FreeMusic(kv.second);

    songs.clear();

    Mix_CloseAudio(); 
}

int AudioManager::LoadClip(std::string path)
{
    Mix_Chunk* sfx = Mix_LoadWAV(path.c_str()); 
    assert(sfx); 

    int id = avaliableIDs.front(); 
    clips.emplace(id, sfx);

    avaliableIDs.pop(); 
    return id;
}

int AudioManager::LoadMusic(std::string path)
{
    Mix_Music* music = Mix_LoadMUS(path.c_str());
    assert(music);

    int id = avaliableIDs.front();
    songs.emplace(id, music);

    avaliableIDs.pop();
    return id;
}

void AudioManager::PlayClip(int ID)
{
    Mix_PlayChannel(ID, clips[ID], 0); // -1 es infinit
}

void AudioManager::StopClip(int ID)
{
    Mix_HaltChannel(ID); 
}

void AudioManager::PlayMusic(int ID)
{
    Mix_FadeInMusic(songs[ID], ID, 500); 
}

void AudioManager::StopMusic(int ID)
{
    Mix_FadeOutChannel(ID, 500); 
}

void AudioManager::FreeClip(int ID)
{
    avaliableIDs.push(ID); 
    Mix_FreeChunk(clips[ID]); 
    clips.erase(ID); 
}

void AudioManager::FreeMusic(int ID)
{
    avaliableIDs.push(ID);
    Mix_FreeMusic(songs[ID]);
    songs.erase(ID);
}

void AudioManager::ClearClips()
{
    clips.clear();
    while (avaliableIDs.size() != 0)
    {
        avaliableIDs.pop();
    }

    for (int i = 0; i < maxChannels; i++)
        avaliableIDs.push(i);
}

void AudioManager::Mute()
{
    if (muted)
        return; 

    // STOP!
   /* Mix_HaltChannel(-1); 
    Mix_HaltMusic(); */
    // CHANGE VOLUME
    Mix_Volume(-1, 0); 
    muted = true; 
}

void AudioManager::Unmute()
{
    if (!muted)
        return;

    Mix_Volume(-1, MIX_MAX_VOLUME); //128
    muted = false; 
}
