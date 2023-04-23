#pragma once

// For uint8_t
#include <stdint.h>

// Represents the type of an individual tile
enum class TileType : uint8_t
{
	Invalid,
	Ground,
	Wall,
	ClosedDoor,
	OpenDoor,
	ClosedChest,
	OpenChest,
	// ... et cetera
};

constexpr uint8_t toTileIndex(TileType tileType)
{
	return static_cast<uint8_t>(tileType);
}

constexpr TileType fromTileIndex(uint8_t tileIndex)
{
	return static_cast<TileType>(tileIndex);
}