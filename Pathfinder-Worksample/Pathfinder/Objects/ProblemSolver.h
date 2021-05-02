#pragma once
#include "WorldObject.h"
#include "../AI/AIController.h"
#include "AnimatedSprite.h"

class ProblemSolver : public WorldObject{
private:
	// Controller for behavior state machine. 
	AIController* aiController_;
	// Graphics component to draw an animated sprite from sprite-sheet
	AnimatedSprite* animatedSprite_;
public:
	ProblemSolver();
	~ProblemSolver();
	void initialize(AnimData animData, unsigned int startingAnimNum, sf::Vector2f startPosition);
	virtual void update(float deltaTime) override;
	virtual void draw(sf::RenderWindow& window) override;

#pragma region friend-Classes "States"
	friend class FindPathState;
	friend class AnimateSolutionState;
	friend class FollowPathState;
	friend class ShowResultState;
	friend class GetNewProblemState;
#pragma endregion
};

