#pragma once
#include "ProblemSolverState.h"
#include "../../Data/ProblemPackage.h"
#include "../../config.h"
#include "../../Services/WorldStateLocator.h"
#include "../../Objects/Maze.h"
#include "FindPathState.h"

class AskForProblemState : public ProblemSolverState {
private:
	WorldState* worldState_;
	MapData newMaze;
	MapData generateRandomMaze(sf::Vector2f characterPosition);

public:
	void update(float deltaTime) override;
	void enter() override;
	AskForProblemState(AIController* parent, AnimatedSprite* ownerAnimator);
};

