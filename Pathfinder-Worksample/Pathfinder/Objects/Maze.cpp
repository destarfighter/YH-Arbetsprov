#include "Maze.h"

Maze::Maze()
: tileMap_(TileMap()) { }

void Maze::setMapData(MapData mapData) {
	tileMap_.setMapData(mapData);
}

void Maze::initialize(std::string tileSetPath, MapData mapData) {
	tileMap_.initialize(tileSetPath, mapData);
}

void Maze::draw(sf::RenderWindow& window) {
	window.draw(tileMap_);
}
