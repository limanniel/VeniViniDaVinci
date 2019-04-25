#include "GameScreenMainMenu.h"
#include "Texture2D.h"


GameScreenMainMenu::GameScreenMainMenu(SDL_Renderer* renderer)
	: GameScreen(renderer)
{
	_mainMenuBG = new Texture2D(renderer);
	if (!_mainMenuBG->LoadFromFile("resources/Images/MainMenu.png")) {
		std::cerr << "Failed to load MainMenuBG Texture!";
	}

	// Set-up Buttons
	SetUpMainMenu();
}


GameScreenMainMenu::~GameScreenMainMenu()
{
	for (unsigned int i = 0; i < 6; i++)
	{
		delete _mainMenuOptions[i];
	}

	delete _mainMenuBG;
	_mainMenuBG = nullptr;
}

void GameScreenMainMenu::Render()
{
	_mainMenuBG->Render(Vector2D(0.0f, 0.0f), SDL_FLIP_NONE, 0.0f);
	for (unsigned int i = 0; i < 6; i++)
	{
		_mainMenuOptions[i]->Render();
	}

}

void GameScreenMainMenu::Update(float deltaTime, SDL_Event event)
{
	// Grab mouse position and make SourceRect out of it.
	int x, y;
	SDL_GetMouseState(&x, &y);
	SDL_Rect mouseRect = { x, y, 16, 16 };

	UpdateButtons(mouseRect, event);

	
}

void GameScreenMainMenu::SetUpMainMenu()
{
	// Main Menu
	int yOffset = 0;
	for (unsigned int i = 0; i < 3; i++)
	{
		_mainMenuOptions[i] = new Text(mRenderer, MarioFont, new SDL_Rect{ 156, 200 + yOffset, 224, 42 });
		yOffset += 70;
	}
	_mainMenuOptions[0]->CreateText("Start Game", _TextColour, _TextAltColour);
	_mainMenuOptions[1]->CreateText("Level Editor", _TextColour, _TextAltColour);
	_mainMenuOptions[2]->CreateText("Quit Game", _TextColour, _TextAltColour);

	// Sub-Menu -> Start game
	yOffset = 0;
	for (unsigned int i = 3; i < 6; i++)
	{
		_mainMenuOptions[i] = new Text(mRenderer, MarioFont, new SDL_Rect{ 156, 200 + yOffset, 224, 42 });
		_mainMenuOptions[i]->SetHidden(true);
		yOffset += 70;
	}
	_mainMenuOptions[3]->CreateText("Single Player", _TextColour, _TextAltColour);
	_mainMenuOptions[4]->CreateText("2 Player", _TextColour, _TextAltColour);
	_mainMenuOptions[5]->CreateText("Back", _TextColour, _TextAltColour);
}

void GameScreenMainMenu::UpdateButtons(SDL_Rect& mouse, SDL_Event event)
{
	for (unsigned int i = 0; i < 6; i++)
	{
		// Check if cursor is hoovering over button
		if (Collisions::Instance()->Box(mouse, *_mainMenuOptions[i]->GetPosition())) {
			_mainMenuOptions[i]->SetHooveredState(true);

			// Check if button is hidden
			if (!_mainMenuOptions[i]->GetHiddenState()) {

				// Check whether button is pressed
				switch (event.type)
				{
				// Apply appropriate action to corresponding button pressed
				case SDL_MOUSEBUTTONDOWN:
					if (event.button.button == SDL_BUTTON_LEFT)
						_mainMenuOptions[i]->SetTriggered(true);
						ButtonAction(i);
					break;

				case SDL_MOUSEBUTTONUP:
					if (event.button.button == SDL_BUTTON_LEFT)
						_mainMenuOptions[i]->SetTriggered(false);
					break;

				default:
					break;
				}
			}
		}
		// Return to original text colour when not hoovered over
		else {
			_mainMenuOptions[i]->SetHooveredState(false);
		}
	}
}

void GameScreenMainMenu::ButtonAction(int index)
{
	switch (index)
	{
	case 0: // Start Game
		FlipMenu();
		break;
	case 1: // Level Ediot
		break;
	case 2: // Quit Game
		QUIT_GAME = true;
		break;
	case 3: // Sub: Single Player
		break;
	case 4: // Sub: 2 Player
		break;
	case 5: // Sub: Back
		FlipMenu();
		break;

	default:
		break;
	}
}

void GameScreenMainMenu::FlipMenu()
{
	for (unsigned int i = 0; i < 6; i++)
	{
		if (_mainMenuOptions[i]->GetHiddenState())
			_mainMenuOptions[i]->SetHidden(false);
		else
			_mainMenuOptions[i]->SetHidden(true);
	}

}
