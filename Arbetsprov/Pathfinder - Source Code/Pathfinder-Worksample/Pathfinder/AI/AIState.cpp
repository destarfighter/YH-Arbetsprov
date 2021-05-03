#include "AIState.h"

AIState::~AIState() { }

AIState::AIState(AIController* parent)
	: parent_(parent) { /* Do Nothing */ }

void AIState::update(float deltaTime) { /* Do Nothing */ }

void AIState::enter() { /* Do Nothing */ }

void AIState::exit() { /* Do Nothing */ }