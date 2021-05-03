#include "StaticSprite.h"

bool StaticSprite::initialize(const int spriteResource, sf::Vector2f position, sf::Color color) {
	// Load sprite texture
	if (!spriteTexture_->loadFromImage(LoadImageFromResource(spriteResource)))
		return false;

	sf::Sprite::setTexture(*spriteTexture_);
	sf::Sprite::setPosition(position);
	sf::Sprite::setColor(color);
	return true;
}

void StaticSprite::draw(sf::RenderWindow& window) {
	window.draw(*this);
}

StaticSprite::StaticSprite()
: spriteTexture_(std::make_shared<sf::Texture>(*(new sf::Texture()))) { }
