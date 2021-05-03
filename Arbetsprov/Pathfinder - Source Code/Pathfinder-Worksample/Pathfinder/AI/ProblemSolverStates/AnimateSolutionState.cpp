#include "AnimateSolutionState.h"

void AnimateSolutionState::update(float deltaTime_) {
	// Check if animation is done
	if (pathAnimater_ptr_->getState() == DONE) {
		if (foundPath_ && path_.size() > 0) {
			// If a path was found, set state to FollowPath
			parent_->setState(new FollowPathState(parent_, ownerAnimator_, path_));
		}
		else {
			// If no path was found, set state to ShowResult - failed
			parent_->setState(new ShowResultState(parent_, ownerAnimator_, foundPath_));
		}
		// remove pathAnimater from WorldState
		auto worldState = WorldStateLocator::getWorldState();
		worldState->removeObject({ "pathAnimation", 5 });
	}
}

void AnimateSolutionState::enter() {
	// initialize PathAnimater
	pathAnimater_ptr_->initialize(CHARACTER_SPRITESHEET_FILE, search_, path_);
	// add pathAnimater to WorldState
	auto worldState = WorldStateLocator::getWorldState();
	worldState->addNewObject({ "pathAnimation", 5 }, pathAnimater_ptr_, true, true);
}

AnimateSolutionState::AnimateSolutionState(AIController* parent, AnimatedSprite* owner, std::vector<unsigned int long> path, std::vector<TileFrame> search, bool foundPath)
: ProblemSolverState(parent, owner)
, path_(path)
, search_(search)
, pathAnimater_ptr_(std::make_shared<PathAnimater>(PathAnimater()))
, foundPath_(foundPath) { }
