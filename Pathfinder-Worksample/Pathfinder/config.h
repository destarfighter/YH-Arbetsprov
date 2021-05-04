#pragma once
#include <vector>
#include "resource.h"

// Render Window
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 544

// Map-Config
#define TILESET_TEXTURE_FILE IDB_PNG2
#define MAP_NAME "maze"
#define TILESIZE 32
#define MAP_WIDTH 25
#define MAP_HEIGHT 17
#define MAP_WALLS std::vector<unsigned int> {1}
#define AMOUNT_OF_WALLS 150
#define TARGET_TILE_INDEX 3
#define START_TILE_INDEX 0
#define FLOOR_TILE_INDEX 0

// PathAnimater
#define EMPTY_TILE_INDEX 6
#define INVESTIGATED_TILE_INDEX 4
#define VISITED_TILE_INDEX 2
#define PATH_TILE_INDEX 5

// AI-Character
#define CHARACTER_SPRITESHEET_FILE IDB_PNG1
#define AI_CHARACTER_NAME "problemSolver"
#define CHARACTER_START_X 10
#define CHARACTER_START_Y 5
#define AI_MOVING_SPEED 50.f

// AI-Character animation states
#define FRAME_RATE 12
#define IDLE_ANIMATION AnimFrameData{ sf::Rect<int>(0, 0, 32, 32), 5, "idle" }
#define WALKING_DOWN_ANIMATION AnimFrameData{ sf::Rect<int>(0, 128, 32, 32), 4, "walking down" }
#define WALKING_RIGHT_ANIMATION AnimFrameData{ sf::Rect<int>(0, 160, 32, 32), 4, "walking right" }
#define WALKING_LEFT_ANIMATION AnimFrameData{ sf::Rect<int>(0, 192, 32, 32), 4, "walking left" }
#define WALKING_UP_ANIMATION AnimFrameData{ sf::Rect<int>(0, 224, 32, 32), 4, "walking up" }
#define THINKING_ANIMATION AnimFrameData{ sf::Rect<int>(0, 0, 32, 32), 5, "thinking" }
#define CELEBRATE_ANIMATION AnimFrameData{ sf::Rect<int>(160, 0, 32, 48), 5, "celebrate" }
#define CRY_ANIMATION AnimFrameData{ sf::Rect<int>(128, 144, 32, 48), 8, "cry" }

// additional sprites
#define SPEECH_BUBBLE_SPRITE_FILE IDB_PNG3
#define SPEECH_BUBBLE_NAME "speechbubble"
#define SPEECH_BUBBLE_OFFSET_X 0
#define SPEECH_BUBBLE_OFFSET_Y -66