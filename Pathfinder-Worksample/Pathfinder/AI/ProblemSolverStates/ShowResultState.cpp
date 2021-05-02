#include "ShowResultState.h"
#include "AskForProblemState.h"

void ShowResultState::update(float deltaTime) {
	if (clock_.getElapsedTime().asSeconds() > waitTime_) {
		parent_->setState(new AskForProblemState(parent_, owner_));
	}
};

void ShowResultState::enter() {
	// Set Animation "Celebrate" or "Cry"
	int animIndex = 0;
	if (foundPath_) {
		animIndex = owner_->getAnimationIndexByName(CELEBRATE_ANIMATION.animName_);
	}
	else {
		animIndex = owner_->getAnimationIndexByName(CRY_ANIMATION.animName_);
	}
	owner_->changeAnim(animIndex);
	// Start clock
	clock_.restart();
};

ShowResultState::ShowResultState(AIController* parent, AnimatedSprite* owner, bool foundPath)
	: ProblemSolverState(parent, owner)
	, foundPath_(foundPath) 
	, clock_(sf::Clock())
	, waitTime_(3) {};