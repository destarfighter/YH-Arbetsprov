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
			ProblemData newProblem{ newMaze, targetPosition };
			// change state to FindPathState
			parent_->setState(new FindPathState(parent_, ownerAnimator_, newProblem));
		}
	}
}

void AskForProblemState::enter() {
	worldState_ = WorldStateLocator::getWorldState();

	// generate maze
	newMaze = generateRandomMaze(ownerAnimator_->getPosition());

	// find maze object in worlState
	auto mazeId = worldState_->getObjectId(MAP_NAME);
	auto maze = worldState_->getObject(mazeId);

	// Cast to Maze and call setMapData with problem update	
	std::static_pointer_cast<Maze>(maze)->setMapData(newMaze);

	// Set greeting animation
	auto animIndex = ownerAnimator_->getAnimationIndexByName(IDLE_ANIMATION.animName_);
	ownerAnimator_->changeAnim(animIndex);

	// Create speech-bubble
	auto speechBubbleSprite_ptr = std::make_shared<StaticSprite>(*(new StaticSprite()));
	sf::Vector2f speechbubblePosition = ownerAnimator_->getPosition();
	speechbubblePosition.x += SPEECH_BUBBLE_OFFSET_X;
	speechbubblePosition.y += SPEECH_BUBBLE_OFFSET_Y;
	speechBubbleSprite_ptr->initialize(SPEECH_BUBBLE_SPRITE_FILE, speechbubblePosition, sf::Color(255, 255, 255, 160));

	// add object to worlState
	worldState_->addNewObject({ SPEECH_BUBBLE_NAME, 30 }, speechBubbleSprite_ptr, true, false);
}

void AskForProblemState::exit() {
	// find speechBubble object and delete it
	auto speechbubbleId = worldState_->getObjectId(SPEECH_BUBBLE_NAME);
	worldState_->removeObject(speechbubbleId);
}

AskForProblemState::AskForProblemState(AIController* parent, AnimatedSprite* ownerAnimator) 
: ProblemSolverState(parent, ownerAnimator)
, newMaze(MapData()) {}
