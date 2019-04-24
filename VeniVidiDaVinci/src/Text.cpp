#include "Text.h"

Text::Text(SDL_Renderer* renderer, TTF_Font* font, SDL_Rect* location)
	: _renderer(renderer), _font(font), _position(location)
{
}


Text::~Text()
{
	SDL_DestroyTexture(_texture);
	if (_altTexture != nullptr)
		SDL_DestroyTexture(_altTexture);
}

void Text::Render()
{
	if (!_hidden) 
	{
		if (_hoovered)
		{
			SDL_RenderCopy(_renderer, _altTexture, nullptr, _position);
		}
		else 
		{
			SDL_RenderCopy(_renderer, _texture, nullptr, _position);
		}
	}
	else 
	{
		
	}
}

void Text::CreateText(const char* text, SDL_Color color, SDL_Color altColor)
{
	_text = text;
	_color = color;
	_altColor = altColor;

	SDL_Surface* surface;
	surface = TTF_RenderText_Solid(_font, _text, _color);
	_texture = SDL_CreateTextureFromSurface(_renderer, surface);

	// Create Alt-Texture if AltColour differs from main colour
	if (
		_color.r != _altColor.r ||
		_color.g != _altColor.g ||
		_color.b != _altColor.b
		)
	{
		surface = TTF_RenderText_Solid(_font, _text, _altColor);
		_altTexture = SDL_CreateTextureFromSurface(_renderer, surface);
	}

	SDL_FreeSurface(surface);
}

void Text::ChangeColour(SDL_Color color)
{
	_color = color;

	SDL_Surface* surface;
	surface = TTF_RenderText_Solid(_font, _text, _color);
	_texture = SDL_CreateTextureFromSurface(_renderer, surface);

	SDL_FreeSurface(surface);
}

void Text::ChangePosition(int xPos, int yPos)
{
	_position->x = xPos;
	_position->y = yPos;
}

void Text::SetHooveredState(bool state)
{
	_hoovered = state;
}

void Text::SetHidden(bool state)
{
	_hidden = state;
}
