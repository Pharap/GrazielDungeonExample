#pragma once

// For uint8_t
#include <stdint.h>

// For PROGMEM
#include <avr/pgmspace.h>

constexpr uint8_t heroSpriteWidth { 8 };
constexpr uint8_t heroSpriteHeight { 8 };

constexpr uint8_t heroSprite[] PROGMEM
{
	// Width, Height
	heroSpriteWidth, heroSpriteHeight,
	
	// Hero_0
	0x60, 0xB0, 0xE4, 0xE6, 0xE6, 0xFE, 0xB2, 0x60,
	
	// Hero_1
	0x7C, 0x20, 0xF4, 0x64, 0x76, 0x9D, 0x60, 0x60,
};
