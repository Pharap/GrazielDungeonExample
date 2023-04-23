#include <Arduboy2.h>

#if defined(FX)
#include <ArduboyFX.h>

#include "FXDATA/data.h"
#endif

#include "Map.h"
#include "Maps.h"
#include "TileType.h"
#include "Tilesheet.h"
#include "HeroSprite.h"

Arduboy2 arduboy;

constexpr uint8_t centreX = (Arduboy2::width() / 2);
constexpr uint8_t centreY = (Arduboy2::height() / 2);

constexpr uint8_t tileWidth = 8;
constexpr uint8_t tileHeight = 8;

constexpr uint8_t heroYMin = 0;
constexpr uint8_t heroYMax = (Arduboy2::height() - tileHeight);

constexpr uint8_t heroXMin = 0;
constexpr uint8_t heroXMax = (Arduboy2::width() - tileWidth);

constexpr uint8_t heroFrameMin = 0;
constexpr uint8_t heroFrameMax = 1;

uint8_t heroX = centreX;
uint8_t heroY = centreY;
uint8_t heroFrame = heroFrameMin;

Map roomMap;

uint8_t mapIndex = 0;

// Load the specified map
void loadIndexedMap(uint8_t index)
{
	roomMap.load(getMap(index));
}

void drawMap()
{
	for(uint8_t tileY = 0; tileY < mapHeight; ++tileY)
		for(uint8_t tileX = 0; tileX < mapWidth; ++tileX)
		{
			// Calculate the y position to draw the tile at.
			int16_t drawY = (tileY * tileHeight);

			// Calculate the x position to draw the tile at.
			int16_t drawX = (tileX * tileWidth);

			// Read the tile from the map.
			TileType tileType = roomMap.getTile(tileX, tileY);

			// Figure out the tile index.
			uint8_t tileIndex = toTileIndex(tileType);

			#if defined(FX)
			// Draw the tile at the calculated position.
			FX::drawBitmap(drawX, drawY, FXdungeon, tileIndex, dbmNormal);
			#else
			// Draw the tile at the calculated position.
			Sprites::drawOverwrite(drawX, drawY, tileSheet, tileIndex);
			#endif
		}
}

void handleInput()
{
	if(arduboy.justPressed(B_BUTTON))
	{
		if (heroFrame < heroFrameMax)
			++heroFrame;
		else
			heroFrame = heroFrameMin;
	}

	if(arduboy.justPressed(UP_BUTTON))
	{
		if(heroY > heroYMin)
			heroY -= tileHeight;
		else
			heroY = heroYMax;
	}

	if(arduboy.justPressed(DOWN_BUTTON))
	{
		if(heroY < heroYMax)
			heroY += tileHeight;
		else
			heroY = heroYMin;
	}

	if(arduboy.justPressed(LEFT_BUTTON))
	{
		if(heroX > heroXMin)
			heroX -= tileWidth;
		else
			heroX = heroXMax;
	}

	if(arduboy.justPressed(RIGHT_BUTTON))
	{
		if(heroX < heroXMax)
			heroX += tileWidth;
		else
			heroX = heroXMin;
	}
	
	if(arduboy.pressed(A_BUTTON))
	{
		if(arduboy.justPressed(UP_BUTTON))
			if(mapIndex < lastMapIndex)
			{
				++mapIndex;
				loadIndexedMap(mapIndex);
			}

		if(arduboy.justPressed(DOWN_BUTTON))
			if(mapIndex > firstMapIndex)
			{
				--mapIndex;
				loadIndexedMap(mapIndex);
			}
	}
}

void drawHero()
{
	#if defined(FX)
	FX::drawBitmap(heroX, heroY, FXhero, heroFrame, dbmNormal);
	#else
	Sprites::drawOverwrite(heroX, heroY, heroSprite, heroFrame);
	#endif
}

void setup()
{
	arduboy.begin();
	arduboy.setFrameRate(15);

	#if defined(FX)
	FX::begin(FX_DATA_PAGE);
	#endif

	// Load map 0
	loadIndexedMap(firstMapIndex);
}

void loop()
{
	if(!arduboy.nextFrame())
		return;

	arduboy.pollButtons();

	handleInput();

	drawMap();
	drawHero();

	#if defined(FX)
	FX::display(CLEAR_BUFFER);
	#else
	arduboy.display(CLEAR_BUFFER);
	#endif
}