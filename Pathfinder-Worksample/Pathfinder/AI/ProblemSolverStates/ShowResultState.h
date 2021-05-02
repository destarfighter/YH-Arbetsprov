#pragma once
#include "ProblemSolverState.h"

class FindPathState;

/// <summary>
/// A State where we display the result of our problem solver atempt. success or failure
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