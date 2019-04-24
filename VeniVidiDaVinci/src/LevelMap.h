#pragma once
#ifndef _LEVELMAP_H
#define _LEVELMAP_H

#include "Constants.h"

class LevelMap
{
private:
	int** mMap;

public:
	LevelMap(int map[MAP_HEIGHT][MAP_WIDTH]);
	~LevelMap();

	void ChangeTileAt(unsigned int row, unsigned int column, unsigned int newValue);
	int GetTileAt(unsigned int h, unsigned int w);
};

#endif
