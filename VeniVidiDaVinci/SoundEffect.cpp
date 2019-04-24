#include "SoundEffect.h"



SoundEffect::SoundEffect(const char* path)
{
	Load(path);
}

SoundEffect::SoundEffect()
{
}

SoundEffect::~SoundEffect()
{
	Mix_FreeChunk(mSoundFile);
	mSoundFile = nullptr;
}

void SoundEffect::Load(const char * path)
{
	mSoundFile = Mix_LoadWAV(path);
	if (mSoundFile == nullptr) {
		std::cerr << "Couldn't load " << path << std::endl;
	}
}

void SoundEffect::SetLooping()
{
	mLoops = -1;
}

void SoundEffect::Play()
{
	Mix_PlayChannel(-1, mSoundFile, mLoops);
}
