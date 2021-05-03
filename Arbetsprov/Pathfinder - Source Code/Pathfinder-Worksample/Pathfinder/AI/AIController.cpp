#include "AIController.h"

void AIController::initialize(AIState* initialState) {
	state_ = initialState;
	state_->enter();
}

void AIController::update(float deltaTime) {
	state_->update(deltaTime);
}

void AIController::setState(AIState* newState) {
	state_->exit();
	delete state_;

	state_ = newState;
	state_->enter();
}
