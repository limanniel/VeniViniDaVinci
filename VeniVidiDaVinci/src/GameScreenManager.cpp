#include "GameScreenManager.h"
#include "GameScreenLevel1.h"
#include "GameScreenMainMenu.h"
#include "GameScreenLevelEditor.h"
#include "GameScreenLevel2.h"

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

void GameScreenManager::Update(double deltaTime, SDL_Event event)
{
	mCurrentScreen->Update(deltaTime, event);
	if (mCurrentScreen->CheckWhetherToQuit())
		QUIT_GAME = true;
	if (mCurrentScreen->CheckWhetherToChangeScreen()) 
		ChangeScreen(mCurrentScreen->GetWhichScreenToChangeTo());
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
	GameScreenLevelEditor* tempLevelEditor;
	GameScreenLevel2* tempLevel2Screen;

	switch (newScreen) {
	case SCREEN_LevelEditor:
		tempLevelEditor = new GameScreenLevelEditor(mRenderer);
		mCurrentScreen = (GameScreen*)tempLevelEditor;
		tempLevelEditor = nullptr;
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
		tempLevel2Screen = new GameScreenLevel2(mRenderer);
		mCurrentScreen = (GameScreen*)tempLevel2Screen;
		tempLevel2Screen = nullptr;
		break;
	case SCREEN_GAMEOVER:
		break;
	case SCREEN_HIGHSCORES:
		break;
	default:
		break;
	}
}