#pragma once
#include <SDL_mixer.h>
#include <iostream>

class SoundEffect
{
private:
	Mix_Chunk* mSoundFile;
	int mLoops{ 0 };

public:
	SoundEffect(const char* path);
	SoundEffect();
	~SoundEffect();

	///<summary> Load a .WAV sound effect </summary> ///
	void Load(const char* path);
	void Play();
	void SetLooping();
};

