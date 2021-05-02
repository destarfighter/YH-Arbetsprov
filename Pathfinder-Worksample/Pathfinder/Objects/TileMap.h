#pragma once
#include <SFML/Graphics.hpp>
#include "../Data/MapPackage.h"

class TileMap : public sf::Drawable, public sf::Transformable {
private:
	// A verttex array containing the mapping data between texture and tile. 
	sf::VertexArray vertices_;
	// A texture containing the tileset for the map. sf::Texture currently causes memory leaks. 
	std::shared_ptr<sf::Texture> tileset_ptr_;
	// data containing size and and tilesize for map
	MapData mapData_;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	TileMap();
	bool initialize(const std::string& tilesetPath, MapData mapData);
	void setMapData(MapData mapData);
	void SetTileData(int tileIndex, int newTextureIndex);
};

