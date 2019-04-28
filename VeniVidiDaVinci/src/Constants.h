#pragma once

//Screen dimensions.
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 512

//Map
#define MAP_HEIGHT 13
#define MAP_WIDTH 16
#define TILE_WIDTH 32
#define TILE_HEIGHT 32

//Jump Related Stuff
#define JUMP_FORCE_DECREMENT 12.0f
#define INITIAL_JUMP_FORCE 52.0f

// Gravity
#define INITIAL_GRAVITY_FORCE 0.05f
#define GRAVITY_INCREMENT 0.05f
#define TERMINAL_GRAVITY_FORCE 0.5f

//Character Data
#define AMOUNT_OF_PLAYERS 2
#define INJURED_TIME 5.0f
constexpr float KOOPA_SPEED = 96.0f;

//Shake
#define SCREENSHAKE_DURATION 100.0f

// Level Editor
#define LE_AMOUNTOFTYPEBLOCKS 8