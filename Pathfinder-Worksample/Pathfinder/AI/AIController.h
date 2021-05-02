#pragma once
#include "AIState.h"

#define AICOMMONLIBRARY_API __declspec(dllexport)

class AICOMMONLIBRARY_API AIController {
private:
	AIState* state_;
public:
	void initialize(AIState* initialState);
	void update(float deltaTime);
	void setState(AIState* newState);
};

