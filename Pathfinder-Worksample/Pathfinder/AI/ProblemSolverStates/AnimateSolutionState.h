#pragma once
#include "ProblemSolverState.h"
#include "../../Objects/PathAnimater.h"
#include "../../config.h"
#include "FollowPathState.h"
#include "ShowResultState.h"
#include "../../Services/WorldStateLocator.h"

class AnimateSolutionState : public ProblemSolverState {
private:
	std::vector<unsigned long int> path_;
	std::vector<TileFrame> search_;
	std::shared_ptr<PathAnimater> pathAnimater_ptr_;
	bool foundPath_;
public:
	void update(float deltaTime_) override;
	void enter() override;
	AnimateSolutionState(
		AIController* parent,
		AnimatedSprite* owner,
		std::vector<unsigned int long> path,
		std::vector<TileFrame> search,
		bool foundPath);
};

