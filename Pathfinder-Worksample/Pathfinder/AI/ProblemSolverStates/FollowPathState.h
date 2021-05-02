#pragma once
#include "../../config.h"
#include "../AIController.h"
#include "ShowResultState.h"

/// <summary>
/// A State where we follow the path represented by an int vector. 
/// </summary>
class FollowPathState : public ProblemSolverState {
private:
	// shortest path to destination
	std::vector<unsigned long int> path_;
	// Moving speed for AI-character "direction"
	float movingSpeed_;
	// Current Direction from currentTile to nextTile
	sf::Vector2i direction_;
	// Current tile the character is moving towards
	unsigned int currentTargetIndex_;

	float getVectorDistance(sf::Vector2f characterPosition, sf::Vector2u targetPosition);
	sf::Vector2i getDirection(sf::Vector2u characterPosition, sf::Vector2u targetPosition);
	sf::Vector2u convertTileToVector(unsigned long int tileIndex, int mapWidth);
	void setAnimationDirection(sf::Vector2i direction);

public:
	void update(float deltaTime) override;
	void enter() override;
	FollowPathState(AIController* parent, AnimatedSprite* owner, std::vector<unsigned long int> path);
};