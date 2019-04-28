#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "Constants.h"
#include "Texture2D.h"
#include "GameScreenManager.h"

//Globals
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
GameScreenManager* gameScrenManager = nullptr;
Uint64 gOldTime; // Delta Time
Mix_Music* gMusic = nullptr;

//Function Prototypes
bool InitSDL();
void LoadMusic(const char* path);
void CloseSDL();
bool Update();
void Render();

int main(int argc, char* args[])
{
	//Check if SDL was set up correctly
	if (InitSDL()) {
		gameScrenManager = new GameScreenManager(gRenderer, SCREEN_MENU);
		gOldTime = SDL_GetPerformanceCounter();
		//LoadMusic("resources/Sounds/Mario.mp3");
		if (Mix_PlayingMusic() == 0) {
			Mix_PlayMusic(gMusic, -1);
		}

		// Flag to check whether to quit engine
		bool quit = false;

		//Game Loop
		while (!quit) {
			Render();
			quit = Update();
		}
	}

	//Close Window and free resources
	CloseSDL();

	return 0;
}

bool InitSDL()
{
	//Setup SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL did not initialise. Error: " << SDL_GetError();
	}

	else {
		//Create Window
		gWindow = SDL_CreateWindow("VeniVidiDaVinci Engine",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		SDL_SetWindowResizable(gWindow, SDL_TRUE);

		//Did the window get created?
		if (gWindow == nullptr) {
			//Failed
			std::cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}

		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

		if (gRenderer != nullptr) {
			// Initialise PNG loading.
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags)) {
				std::cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
				return false;
			}
		}

		else {
			std::cout << "Renderer could not initialise. Error: " << SDL_GetError();
			return false;
		}

		// Initialise Mixer
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)) {
			std::cerr << "Mixer could not initialise. Error: " << Mix_GetError();
			return false;
		}

		// Initialise TTF Lib
		if (TTF_Init() == 1) {
			std::cerr << "TTF could not initialise. Error: " << TTF_GetError();
			return false;
		}
	}
	// return true if all's good
	return true;
}

void LoadMusic(const char* path)
{
	//gMusic = Mix_LoadMUS(path);
	if (gMusic == nullptr) {
		std::cerr << "Failed to load background music! Error: " << Mix_GetError() << std::endl;
	}
}

void CloseSDL()
{
	//Destroy game screen manager
	delete gameScrenManager;
	gameScrenManager = nullptr;

	// Release Mixer
	Mix_FreeMusic(gMusic);
	gMusic = nullptr;

	// Release renderer
	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;

	//Release the window
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	//Quit SDL subsystems
	Mix_Quit();
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

bool Update()
{
	//Get the new time
	Uint64 newTime = SDL_GetPerformanceCounter();

	//Event Handler
	SDL_Event event;

	//Get the events.
	SDL_PollEvent(&event);

	switch (event.type) {
		//Click "X" to quit.
	case SDL_QUIT:
		return true;
		break;

	//	//Exit engine upon Q key press
	//case SDL_KEYDOWN:
	//	switch (event.key.keysym.sym) {
	//		// Q
	//	case SDLK_q:
	//		return true;
	//		//break;
	//	}
	}
	gameScrenManager->Update((float)((newTime - gOldTime) * 1000 / (float)SDL_GetPerformanceFrequency()), event);
	gOldTime = newTime;

	if (gameScrenManager->CheckWhetherToQuit())
		return true;

	return false;
}

void Render()
{
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);

	gameScrenManager->Render();

	SDL_RenderPresent(gRenderer);
}