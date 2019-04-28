#pragma once
#ifndef _TEXTURE2D_H
#define _TEXTURE2D_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Commons.h"

class Texture2D
{
private:
	SDL_Renderer* mRenderer;
	SDL_Texture* mTexture;

	int mWidth;
	int mHeight;

public:
	Texture2D(SDL_Renderer* renderer);
	~Texture2D();

	bool LoadFromFile(const char* path);
	void Free();
	void Render(Vector2D newPosition, SDL_RendererFlip flip, double angle = 0.0f);
	void Render(SDL_Rect sourceRect, SDL_RendererFlip flip, double angle = 0.0f);
	void Render(SDL_Rect sourceRect, SDL_Rect positionRect, SDL_RendererFlip flip, double angle = 0.0f);

	// Getters
	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight; }
};

#endif //_TEXTURE2D_H
