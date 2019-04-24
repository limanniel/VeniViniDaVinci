#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "Commons.h"

class Text
{
private:
	SDL_Renderer* _renderer{ nullptr };
	SDL_Rect* _position{ nullptr };

	// Button Properties
	const char* _text{ "" };
	TTF_Font* _font{ nullptr };
	SDL_Color _color{ 255,255,255 };
	SDL_Color _altColor{ 255,255,255 };
	SDL_Texture* _texture{ nullptr };
	SDL_Texture* _altTexture{ nullptr };

	// Button States
	bool _hoovered{ false };
	bool _hidden{ false };
	bool _triggered{ false };

public:
	Text(SDL_Renderer* renderer, TTF_Font* font, SDL_Rect* location);
	~Text();

	void Render();

	void CreateText(const char* text, SDL_Color color, SDL_Color altColor = {255,255,255});
	void ChangeColour(SDL_Color color);
	void ChangePosition(int xPos, int yPos);

	void SetHooveredState(bool state);
	void SetTriggered(bool state);
	void SetHidden(bool state);

	inline SDL_Rect* GetPosition() const { return _position; }
	inline bool GetTriggeredState() const { return _triggered; }
	inline bool GetHiddenState() const { return _hidden; }
};

