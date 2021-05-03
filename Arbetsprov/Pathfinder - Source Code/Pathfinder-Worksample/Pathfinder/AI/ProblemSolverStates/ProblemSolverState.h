#pragma once
#include "../AIState.h"
#include "../../Objects/AnimatedSprite.h"

/// <summary>
/// The Base-State for the ProblemSolver character. 
/// Adds a pointer to the characters animation-component for animation-changes and positional updates.
/// </summary>
class ProblemSolverState : public AIState {
protected:
	AnimatedSprite* ownerAnimator_;

public:
	ProblemSolverState(AIController* parent, AnimatedSprite* ownerAnimator_)
		: AIState(parent)
		, ownerAnimator_(ownerAnimator_) {};
};

