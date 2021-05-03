#pragma once
#include "ProblemSolverState.h"

class FindPathState;

/// <summary>
/// A State for the ProblemSolver where a result is shown. if a path was found - success, if not - failure
/// </summary>
class ShowResultState : public ProblemSolverState {
private:
	bool foundPath_;
	sf::Clock clock_;
	int waitTime_;

public:
	void update(float deltaTime) override;
	void enter() override;
	ShowResultState(AIController* parent, AnimatedSprite* owner, bool foundPath);
};