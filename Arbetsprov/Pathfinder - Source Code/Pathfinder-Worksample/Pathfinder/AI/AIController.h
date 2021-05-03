#pragma once
#include "AIState.h"

/// <summary>
/// A Controller to manage the active state of an ai-character.
/// </summary>
class AIController {
private:
	AIState* state_;
public:
	void initialize(AIState* initialState);
	void update(float deltaTime);
	void setState(AIState* newState);
};

