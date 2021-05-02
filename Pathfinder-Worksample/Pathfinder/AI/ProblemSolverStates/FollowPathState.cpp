#include "FollowPathState.h"

float FollowPathState::getVectorDistance(sf::Vector2f characterPosition, sf::Vector2u targetPosition) {
	return sqrt(pow((targetPosition.x) - characterPosition.x, 2) +
		pow((targetPosition.y) - characterPosition.y, 2) * 1.0);
}

sf::Vector2i FollowPathState::getDirection(sf::Vector2u characterPosition, sf::Vector2u targetPosition) {
	// Subtract start point from target to get direction vector
	auto result = static_cast<sf::Vector2i>((targetPosition)-characterPosition);
	// calculate magnitude of result vector
	float magnitude = sqrt((result.x * result.x) + (result.y * result.y));
	// normalize result vector
	result.x = result.x / magnitude;
	result.y = result.y / magnitude;
	return result;
}

sf::Vector2u FollowPathState::convertTileToVector(unsigned long int tileIndex, int mapWidth) {
	return sf::Vector2u((tileIndex % mapWidth) * TILESIZE, (tileIndex / mapWidth) * TILESIZE);
}

void FollowPathState::setAnimationDirection(sf::Vector2i direction) {
	// set new animation
	int animIndex = 0;
	if (direction_.x > 0)
		animIndex = owner_->getAnimationIndexByName(WALKING_RIGHT_ANIMATION.animName_);
	else if (direction_.x < 0)
		animIndex = owner_->getAnimationIndexByName(WALKING_LEFT_ANIMATION.animName_);
	else if (direction_.y > 0)
		animIndex = owner_->getAnimationIndexByName(WALKING_DOWN_ANIMATION.animName_);
	else if (direction_.y < 0)
		animIndex = owner_->getAnimationIndexByName(WALKING_UP_ANIMATION.animName_);
	owner_->changeAnim(animIndex);
}

	void FollowPathState::update(float deltaTime) {
		// move character
		owner_->move(direction_.x * movingSpeed_ * deltaTime,
			direction_.y * movingSpeed_ * deltaTime);

		if (getVectorDistance(owner_->getPosition(), convertTileToVector(path_[currentTargetIndex_], MAP_WIDTH)) < 0.1f) {

			// snap character to position
			owner_->setPosition(static_cast<sf::Vector2f>(convertTileToVector(path_[currentTargetIndex_], MAP_WIDTH)));

			currentTargetIndex_++;
			if (currentTargetIndex_ == path_.size()) {
				// Character has reached goal.
				parent_->setState(new ShowResultState(parent_, owner_, true));
				return;
			}

			// get new direction
			auto newDirection = getDirection(static_cast<sf::Vector2u>(owner_->getPosition()),
				convertTileToVector(path_[currentTargetIndex_], MAP_WIDTH));

			if (newDirection != direction_) {
				// Set new direction
				direction_ = newDirection;
				setAnimationDirection(direction_);
			}
		}
	};
 
	void FollowPathState::enter() {
		direction_ = getDirection(static_cast<sf::Vector2u>(owner_->getPosition()),
			convertTileToVector(path_[currentTargetIndex_], MAP_WIDTH));
		setAnimationDirection(direction_);
	};

	FollowPathState::FollowPathState(AIController* parent, AnimatedSprite* owner, std::vector<unsigned long int> path)
		: ProblemSolverState(parent, owner)
		, path_(path)
		, movingSpeed_(AI_MOVING_SPEED)
		, currentTargetIndex_(0) {};
