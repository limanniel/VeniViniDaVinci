#include "Texture2D.h"

Texture2D::Texture2D(SDL_Renderer* renderer)
	: mRenderer(renderer), mTexture(nullptr), mWidth(0), mHeight(0)
{
}

Texture2D::~Texture2D()
{
	// Free up the memory
	Free();

	mRenderer = nullptr;
}

bool Texture2D::LoadFromFile(const char* path)
{
	// Free space
	Free();
	//Load the image
	SDL_Surface* tempSurface = IMG_Load(path);

	//Create the texture from the pixels on the surface
	if (tempSurface != nullptr) {
		mTexture = SDL_CreateTextureFromSurface(mRenderer, tempSurface);
		mWidth = tempSurface->w;
		mHeight = tempSurface->h;

		if (mTexture == nullptr) {
			std::cout << "Unable to create texture from surface. Error: " << SDL_GetError() << std::endl;
		}
		//Colour key the image - the colour to be transparent
		SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 0, 0xFF, 0xFF));

		SDL_FreeSurface(tempSurface); // Delete temp surface
	}

	else {
		std::cout << "Unable to create texture from surface. Error: " << IMG_GetError() << std::endl;
	}

	return mTexture != nullptr;
}

void Texture2D::Free()
{
	if (mTexture != nullptr) {
		SDL_DestroyTexture(mTexture);

		mWidth = 0;
		mHeight = 0;
		mTexture = nullptr;
	}
}

void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, double angle)
{
	//Set where to render the texture
	SDL_Rect renderLocation = { newPosition.x, newPosition.y, mWidth, mHeight };

	//Render to screen
	SDL_RenderCopyEx(mRenderer, mTexture, nullptr, &renderLocation, 0, nullptr, flip);
}

void Texture2D::Render(SDL_Rect sourceRect, SDL_Rect positionRect, SDL_RendererFlip flip, double angle)
{
	//Render to scree
	SDL_RenderCopyEx(mRenderer, mTexture, &sourceRect, &positionRect, angle, nullptr, flip);
}