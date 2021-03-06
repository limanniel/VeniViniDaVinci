#include "Tile.h"



Tile::Tile(Texture2D* texture, Vector2D position)
{
	_texture = texture;
	_width = _texture->GetWidth();
	_height = _texture->GetHeight();
	_sourceRect = new SDL_Rect{ (int)position.x, (int)position.y, _width, _height };
}

Tile::Tile(SDL_Renderer* renderer, TileTypes type, Vector2D position)
{
	_texture = new Texture2D(renderer);
	switch (type)
	{
	case TileTypes::NONE:
		_texture->LoadFromFile("resources/Images/LevelEditor/0.png");
		break;
	case TileTypes::PLATFORM:
		_texture->LoadFromFile("resources/Images/LevelEditor/1.png");
		break;
	case TileTypes::POW:
		_texture->LoadFromFile("resources/Images/LevelEditor/2.png");
		break;
	case TileTypes::COIN:
		_texture->LoadFromFile("resources/Images/LevelEditor/3.png");
		break;
	case TileTypes::RIGHT_PIPE:
		_texture->LoadFromFile("resources/Images/LevelEditor/4.png");
		break;
	case TileTypes::LEFT_PIPE:
		_texture->LoadFromFile("resources/Images/LevelEditor/5.png");
		break;
	case TileTypes::MARIO_SPAWN:
		_texture->LoadFromFile("resources/Images/LevelEditor/6.png");
		break;
	default:
		break;
	}
	_width = _texture->GetWidth();
	_height = _texture->GetHeight();
	_sourceRect = new SDL_Rect{ (int)position.x, (int)position.y, _width, _height };
}


Tile::~Tile()
{
	delete _sourceRect;
	_sourceRect = nullptr;
}

void Tile::Render(Vector2D position)
{
	SDL_Rect tempRect = { (int)position.x, (int)position.y, 32, 32 };
	SDL_Rect textRect = { 0, 0, 32, 32 };
	_texture->Render(textRect, tempRect, SDL_FLIP_NONE, 0.0f);
}

void Tile::Render(float xOffset, float yOffset)
{
	Vector2D tempRect = { _sourceRect->x + xOffset, _sourceRect->y + yOffset};
	_texture->Render(tempRect, SDL_FLIP_NONE, 0.0f);
}

void Tile::Update(float deltaTime)
{
}

