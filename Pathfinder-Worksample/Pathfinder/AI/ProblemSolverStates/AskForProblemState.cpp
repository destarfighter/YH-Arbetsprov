#include "AskForProblemState.h"

MapData AskForProblemState::generateRandomMaze(sf::Vector2f characterPosition) {
	srand(time(NULL));
	// Create base n x n tile
	std::vector<int> tileData(MAP_HEIGHT * MAP_WIDTH, FLOOR_TILE_INDEX);

	// Randomize walls locations
	for (unsigned int i = 0; i < AMOUNT_OF_WALLS; ++i) {
		tileData[rand() % tileData.size()] = MAP_WALLS[rand() % MAP_WALLS.size()];
	}

	// Set current character-position to be open
	tileData[((characterPosition.y / TILESIZE) * MAP_WIDTH) + (characterPosition.x / TILESIZE)] = START_TILE_INDEX;
	// Create MapData package
	return MapData { sf::Vector2u(TILESIZE, TILESIZE), tileData, MAP_WIDTH, MAP_HEIGHT };
}

void AskForProblemState::update(float deltaTime) {
	// Check for input to choose target
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

		// check that selected position is within the window
		auto localMousePosition = sf::Mouse::getPosition(worldState_->getWindow());
		if (localMousePosition.x < WINDOW_WIDTH && localMousePosition.x > 0
			&& localMousePosition.y < WINDOW_HEIGHT && localMousePosition.y > 0) {
			
			// Convert mouse-position to tile-map coordinates
			sf::Vector2u targetPosition(localMousePosition.x / TILESIZE, localMousePosition.y / TILESIZE);

			// update maze with new targetPosition
			newMaze.tiles_[(MAP_WIDTH * targetPosition.y) + targetPosition.x] = TARGET_TILE_INDEX;

			// find maze object in worlState
			auto mazeId = worldState_->getObjectId(MAP_NAME);
			auto maze = worldState_->getObject(mazeId);
			// Cast to Maze and call setMapData with problem update	
			std::static_pointer_cast<Maze>(maze)->setMapData(newMaze);

			// create problemdefinition
			ProblemDefinition newProblem{ newMaze, targetPosition };
			// change state to FindPathState
			parent_->setState(new FindPathState(parent_, owner_, newProblem));
		}
	}
}

void AskForProblemState::enter() {
	// generate maze
	newMaze = generateRandomMaze(owner_->getPosition());

	// find maze object in worlState
	auto mazeId = worldState_->getObjectId(MAP_NAME);
	auto maze = worldState_->getObject(mazeId);

	// Cast to Maze and call setMapData with problem update	
	std::static_pointer_cast<Maze>(maze)->setMapData(newMaze);

	// Set greeting animation
	auto animIndex = owner_->getAnimationIndexByName(IDLE_ANIMATION.animName_);
	owner_->changeAnim(animIndex);

	// Create speech-bubble animation
}

AskForProblemState::AskForProblemState(AIController* parent, AnimatedSprite* ownerAnimator) 
: ProblemSolverState(parent, ownerAnimator)
, worldState_(WorldStateLocator::getWorldState())
, newMaze(MapData()) {}
