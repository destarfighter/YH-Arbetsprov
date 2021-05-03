#pragma once
#include "SFML/Graphics.hpp"
#include "WorldObject.h"
#include "../ResourceLoader.h"

/// <summary>
/// An object that can initialize and draw a static-sprite to the screen. 
/// </summary>
class StaticSprite : public sf::Sprite, public WorldObject{
private:
	std::shared_ptr<sf::Texture> spriteTexture_;
public:
	bool initialize(const int spriteResource, sf::Vector2f position, sf::Color color = sf::Color(255, 255, 255, 255));
	void draw(sf::RenderWindow& window);
	StaticSprite();
};

