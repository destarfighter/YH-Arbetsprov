#pragma once
#include <future>
#include "../AIController.h"
#include "ProblemSolverState.h"
#include "../Pathfinder.h"
#include "../../Data/ProblemPackage.h"
#include "AnimateSolutionState.h"

/// <summary>
/// The State for the ProblemSolver where it is supposed to asynchroniously retrieve the shortest path from point A to point B. 
/// </summary>
class FindPathState : public ProblemSolverState {
private:
	Pathfinder pathfinder_;
	std::future<std::vector<unsigned long int>> path_;
	ProblemData problemDefinition_;
	sf::Clock clock_;
	int waitTime_;

public:
	void update(float deltaTime) override;
	void enter() override;
	FindPathState(AIController* parent, AnimatedSprite* owner, ProblemData problemDefinition);
};