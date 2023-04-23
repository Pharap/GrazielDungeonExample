#pragma once

// For uint8_t
#include <stdint.h>

// For PROGMEM
#include <avr/pgmspace.h>

#include "Maps.h"
#include "TileType.h"

class Map
{
private:
	TileType data[mapHeight][mapWidth];
	
public:
	// Retrieves a tile from the map
	TileType getTile(uint8_t x, uint8_t y) const
	{
		if((x > mapWidth) || (y > mapHeight))
			return TileType::Invalid;
	
		return this->data[y][x];
	}
	
	// Overwrites a tile in the map
	void setTile(uint8_t x, uint8_t y, TileType tile)
	{
		if((x > mapWidth) || (y > mapHeight))
			return;
	
		this->data[y][x] = tile;
	}
	
	// Loads a map
	void load(const uint8_t * data)
	{
		// Copies a map from progmem into RAM
		memcpy_P(this->data, data, sizeof(this->data));
	}
};