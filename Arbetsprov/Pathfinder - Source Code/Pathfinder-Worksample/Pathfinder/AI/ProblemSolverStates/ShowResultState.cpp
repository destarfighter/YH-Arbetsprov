#include "ShowResultState.h"
#include "AskForProblemState.h"

void ShowResultState::update(float deltaTime) {
	// Makes sure that the result-animation is displayed for a set amount of time before changing state again. 
	if (clock_.getElapsedTime().asSeconds() > waitTime_) {
		parent_->setState(new AskForProblemState(parent_, ownerAnimator_));
	}
};

void ShowResultState::enter() {
	// Set Animation "Celebrate" or "Cry"
	int animIndex = 0;
	if (foundPath_) {
		animIndex = ownerAnimator_->getAnimationIndexByName(CELEBRATE_ANIMATION.animName_);
	}
	else {
		animIndex = ownerAnimator_->getAnimationIndexByName(CRY_ANIMATION.animName_);
	}
	ownerAnimator_->changeAnim(animIndex);
	// Start clock
	clock_.restart();
};

ShowResultState::ShowResultState(AIController* parent, AnimatedSprite* owner, bool foundPath)
	: ProblemSolverState(parent, owner)
	, foundPath_(foundPath) 
	, clock_(sf::Clock())
	, waitTime_(3) {};