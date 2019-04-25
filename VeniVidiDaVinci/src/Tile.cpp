#include "Tile.h"



Tile::Tile(Texture2D* texture)
{
	_texture = texture;
	_width = _texture->GetWidth();
	_height = _texture->GetHeight();
	//_sourceRect = new SDL_Rect{ (int)position.x, (int)position.y, _width, _height };
}


Tile::~Tile()
{
	delete _sourceRect;
	_sourceRect = nullptr;
}

void Tile::Render(Vector2D position)
{
	_texture->Render(Vector2D(position.x, position.y), SDL_FLIP_NONE, 0.0f);
}
