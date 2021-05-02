#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "TileMap.h"
#include "WorldObject.h"
#include "../config.h"

enum PathAnimaterState {
	DRAWING_SEARCH = 0,
	DRAWING_PATH = 1,
	DONE = 2
};

enum TileType {
	INVESTIGATED_TILE = INVESTIGATED_TILE_INDEX,
	VISITED_TILE = VISITED_TILE_INDEX
};

struct TileFrame {
	long int tileIndex_;
	TileType tileType_;
};

class PathAnimater : public WorldObject {
private:
	TileMap tileMap_;
	// All the animation data (the steps performed in order during the search, investigated/visited tiles)
	std::vector<TileFrame> searchAnimation_;
	// The path from start to target represented by integer index. 
	std::vector<unsigned long int> pathAnimation_;
	// The frame number of the active tile that's being displayed
	unsigned int frameNum_; 
	// Anmount of time the current frame has been displayed
	float frameTime_;
	// The FPS the animation is running at
	float animFps_;
	// State of pathAnimater to draw different parts of animation
	PathAnimaterState state_;

public:
	void initialize(const std::string& tilesetPath, std::vector<TileFrame> searchAnimation, std::vector<unsigned long int> pathAnimation);
	virtual void update(float deltaTime) override;
	virtual void draw(sf::RenderWindow& window) override;
	PathAnimaterState getState() { return state_; };
	PathAnimater();
};

