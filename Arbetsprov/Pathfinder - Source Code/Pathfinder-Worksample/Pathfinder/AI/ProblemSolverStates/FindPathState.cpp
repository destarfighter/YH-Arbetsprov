#include "FindPathState.h"

void FindPathState::update(float deltaTime) {
	// Check if async pathfinder is ready
	if (path_._Is_ready()) {
		// Check minimum amount of time for FindPathState. Padding for smooth running of application
		if (clock_.getElapsedTime().asSeconds() > waitTime_) {
			// Set stat to AnimateSoution
			parent_->setState(new AnimateSolutionState(parent_, ownerAnimator_, path_.get(), pathfinder_.getSearchProcess(), pathfinder_.getPathWasFound()));
		}
	}
}

void FindPathState::enter() {
	// Start async call to pathfinder with a promise to get a path later. 
	path_ = std::async(&Pathfinder::findPath, &pathfinder_, ownerAnimator_->getPosition(), problemDefinition_.destination_, problemDefinition_.mapData_);

	// Set thinking animation
	auto animIndex = ownerAnimator_->getAnimationIndexByName(IDLE_ANIMATION.animName_);
	ownerAnimator_->changeAnim(animIndex);

	// Start clock
	clock_.restart();
}

FindPathState::FindPathState(AIController* parent, AnimatedSprite* owner, ProblemData problemDefinition)
	: ProblemSolverState(parent, owner)
	, problemDefinition_(problemDefinition)
	, clock_(sf::Clock())
	, waitTime_(1) { }
