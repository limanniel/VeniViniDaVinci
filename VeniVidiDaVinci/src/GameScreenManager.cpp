#include "GameScreenManager.h"
#include "GameScreenMainMenu.h"
#include "GameScreenLevelEditor.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"
#include "GameScreenGameOver.h"

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

	GameScreenMainMenu* tempMainMenu;
	GameScreenLevelEditor* tempLevelEditor;
	GameScreenLevel1* tempLevel1Screen;
	GameScreenLevel2* tempLevel2Screen;
	GameScreenGameOver* tempGameOver;

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
		tempLevel1Screen = new GameScreenLevel1(mRenderer);
		mCurrentScreen = (GameScreen*)tempLevel1Screen;
		tempLevel1Screen = nullptr;
		break;
	case SCREEN_LEVEL2:
		tempLevel2Screen = new GameScreenLevel2(mRenderer);
		mCurrentScreen = (GameScreen*)tempLevel2Screen;
		tempLevel2Screen = nullptr;
		break;
	case SCREEN_GAMEOVER:
		tempGameOver = new GameScreenGameOver(mRenderer);
		mCurrentScreen = (GameScreen*)tempGameOver;
		tempGameOver = nullptr;
		break;
	case SCREEN_HIGHSCORES:
		break;
	default:
		break;
	}
}