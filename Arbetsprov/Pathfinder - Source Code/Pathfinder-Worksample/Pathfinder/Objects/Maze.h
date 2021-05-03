#pragma once
#include <SFML/Graphics.hpp>
#include "WorldObject.h"
#include "TileMap.h"
#include "../Data/MapPackage.h"

/// <summary>
/// A Maze that is defined by a TileMap and can update its content
/// </summary>
class Maze : public WorldObject {
	TileMap tileMap_;

public:
	Maze();
	void setMapData(MapData mapData);
	void initialize(int tileSetResource, MapData mapData);
	virtual void draw(sf::RenderWindow& window) override;
};

