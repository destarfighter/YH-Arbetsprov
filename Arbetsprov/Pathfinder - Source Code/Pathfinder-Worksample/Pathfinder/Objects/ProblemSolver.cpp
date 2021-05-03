#include "ProblemSolver.h"
#include "../AI/ProblemSolverStates/AskForProblemState.h"


void ProblemSolver::update(float deltaTime) {
	// Update Animation
	animatedSprite_->update(deltaTime);
	// Update character based on current state
	aiController_->update(deltaTime);
}

void ProblemSolver::draw(sf::RenderWindow& window) {
	window.draw(*animatedSprite_);
}

ProblemSolver::ProblemSolver()
	: aiController_(new AIController())
	, animatedSprite_(new AnimatedSprite()) { }

ProblemSolver::~ProblemSolver() {
	delete animatedSprite_;
	delete aiController_;
}

void ProblemSolver::initialize(AnimData animData, unsigned int startingAnimNum, sf::Vector2f startPosition) {
	// Set Starting positions of animated sprite. 
	animatedSprite_->setPosition(startPosition);
	// Initialize AnimationSprite
	animatedSprite_->initialize(animData, startingAnimNum);
	// Set state for ai controller
	aiController_->initialize(new AskForProblemState(aiController_ ,animatedSprite_));
}
