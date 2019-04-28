#pragma once
#include "GameScreen.h"
#include "Texture2D.h"

class GameScreenGameOver : public GameScreen
{
private:
	Texture2D* _bgTexture{ nullptr };

	SDL_Color _textColour{ 255, 255, 255 };
	SDL_Color _altTextColour{ 255, 146, 30 };
	Text* _ReturnToMainMenu{ nullptr };

public:
	GameScreenGameOver(SDL_Renderer* renderer);
	~GameScreenGameOver();

	void Render() override;
	void Update(float deltaTime, SDL_Event event) override;
};

