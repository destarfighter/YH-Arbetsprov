#pragma once
#include "ProblemSolverState.h"
#include "../../Data/ProblemPackage.h"
#include "../../config.h"
#include "../../Services/WorldStateLocator.h"
#include "../../Objects/Maze.h"
#include "FindPathState.h"
#include "../../Objects/StaticSprite.h"

/// <summary>
/// A State for a ProblemSolver that asks the user for a new target position.
/// </summary>
class AskForProblemState : public ProblemSolverState {
private:
	WorldState* worldState_;
	MapData newMaze;
	MapData generateRandomMaze(sf::Vector2f characterPosition);

public:
	void update(float deltaTime) override;
	void enter() override;
	void exit() override;
	AskForProblemState(AIController* parent, AnimatedSprite* ownerAnimator);
};

