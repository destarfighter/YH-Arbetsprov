#include "AIState.h"

AIState::~AIState() { }

AIState::AIState(AIController* parent)
	: parent_(parent) {}

void AIState::update(float deltaTime) {}

void AIState::enter() {}

void AIState::exit() {}