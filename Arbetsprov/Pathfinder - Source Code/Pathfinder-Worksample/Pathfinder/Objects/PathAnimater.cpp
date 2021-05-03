#include "PathAnimater.h"

void PathAnimater::initialize(const int tilesetResource, std::vector<TileFrame> searchAnimation, std::vector<unsigned long int> pathAnimation) {
	searchAnimation_ = searchAnimation;
	pathAnimation_ = pathAnimation;
	// Create empty map
	std::vector<int> emptyMap(MAP_WIDTH * MAP_HEIGHT, EMPTY_TILE_INDEX);
	MapData mapData = {sf::Vector2u(TILESIZE, TILESIZE), emptyMap, MAP_WIDTH, MAP_HEIGHT};
	tileMap_.initialize(TILESET_TEXTURE_FILE, mapData);
}

void PathAnimater::update(float deltaTime) {
	frameTime_ += deltaTime;

	switch (state_)
	{
	case DRAWING_SEARCH:
		// Check if next frame should be drawn
		if (frameTime_ > (1 / animFps_)) {
			// If end of search has been drawn, change state and start drawing path
			if (frameNum_ == searchAnimation_.size()) {
				state_ = DRAWING_PATH;
				frameTime_ = 0;
				frameNum_ = 0;
				return;
			}
			// Change map in tilemap to "search" or "visited" texture
			tileMap_.SetTileData(searchAnimation_[frameNum_].tileIndex_, searchAnimation_[frameNum_].tileType_);
			// Make sure frametime wraps correctly
			frameTime_ = std::fmod(frameTime_, 1 / animFps_);
			frameNum_++;
		}
		break;
	case DRAWING_PATH:
		// Check if next frame should be drawn
		if (frameTime_ > (1 / animFps_)) {
			// If end of path-animation has been reached, change state to Done
			if (frameNum_ == pathAnimation_.size()) {
				state_ = DONE;
				return;
			}
			tileMap_.SetTileData(pathAnimation_[frameNum_], PATH_TILE_INDEX);
			// Make sure frametime wraps correctly
			frameTime_ = std::fmod(frameTime_, 1 / animFps_);
			frameNum_++;
		}
		break;
	}
}

void PathAnimater::draw(sf::RenderWindow& window) {
	window.draw(tileMap_);
}

PathAnimater::PathAnimater()
: tileMap_(TileMap())
, searchAnimation_(std::vector<TileFrame>())
, frameNum_(0)
, frameTime_(0)
, animFps_(24)
, state_(DRAWING_SEARCH) {}
