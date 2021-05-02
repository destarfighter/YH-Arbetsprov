#include "FindPathState.h"

void FindPathState::update(float deltaTime) {
	if (path_._Is_ready()) {
		if (clock_.getElapsedTime().asSeconds() > waitTime_) {
			parent_->setState(new AnimateSolutionState(parent_, owner_, path_.get(), pathfinder_.getSearchProcess(), pathfinder_.getFoundPath()));
		}
	}
}

void FindPathState::enter() {
	path_ = std::async(&Pathfinder::findPath, &pathfinder_, owner_->getPosition(), problemDefinition_.destination_, problemDefinition_.mapData_);

	// Set thinking animation
	auto animIndex = owner_->getAnimationIndexByName(IDLE_ANIMATION.animName_);
	owner_->changeAnim(animIndex);

	// Start clock
	clock_.restart();
}

FindPathState::FindPathState(AIController* parent, AnimatedSprite* owner, ProblemDefinition problemDefinition)
	: ProblemSolverState(parent, owner)
	, problemDefinition_(problemDefinition)
	, clock_(sf::Clock())
	, waitTime_(1) { }
