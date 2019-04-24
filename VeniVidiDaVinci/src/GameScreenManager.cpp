#include "GameScreenManager.h"
#include "GameScreenLevel1.h"
#include "GameScreenMainMenu.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
	: mRenderer(renderer), mCurrentScreen(nullptr)
{
	this->mRenderer = renderer;
	// Esnure first screen is up
	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager()
{
	delete mCurrentScreen;
	mCurrentScreen = nullptr;

	mRenderer = nullptr;
}

void GameScreenManager::Update(float deltaTime, SDL_Event event)
{
	if (mCurrentScreen->CheckWhetherToQuit())
		QUIT_GAME = true;

	mCurrentScreen->Update(deltaTime, event);
}

void GameScreenManager::Render()
{
	mCurrentScreen->Render();
}

void GameScreenManager::ChangeScreen(SCREENS newScreen)
{
	//Clear up the old screen.
	if (mCurrentScreen != nullptr) {
		delete mCurrentScreen;
	}

	GameScreenLevel1* tempScreen;
	GameScreenMainMenu* tempMainMenu;

	switch (newScreen) {
	case SCREEN_INTRO:
		break;
	case SCREEN_MENU:
		tempMainMenu = new GameScreenMainMenu(mRenderer);
		mCurrentScreen = (GameScreen*)tempMainMenu;
		tempMainMenu = nullptr;
		break;
	case SCREEN_LEVEL1:
		tempScreen = new GameScreenLevel1(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreen;
		tempScreen = nullptr;
		break;
	case SCREEN_LEVEL2:
		break;
	case SCREEN_GAMEOVER:
		break;
	case SCREEN_HIGHSCORES:
		break;
	default:
		break;
	}
}