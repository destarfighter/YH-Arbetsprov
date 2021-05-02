#include <SFML/Graphics.hpp>
#include "Services/WorldState.hpp"
#include "Services/WorldStateLocator.h"
#include "Objects/ProblemSolver.h"
#include "Objects/Maze.h"
#include "Data/MapPackage.h"
#include "AI/ProblemSolverStates/ProblemSolverState.h"
#include "config.h"

std::shared_ptr<sf::Texture> loadTexture(std::string texturePath) {
	auto texture_ptr = std::make_shared<sf::Texture>();
	if (!texture_ptr->loadFromFile(texturePath))
		throw std::exception("Failed to load image from file.");
	return texture_ptr;
}

std::shared_ptr<ProblemSolver> createProblemSolver() {
	auto texture = loadTexture(CHARACTER_SPRITESHEET_FILE);
	texture->setSmooth(true);
	texture->setRepeated(false);

	auto frameInfo = std::vector<AnimFrameData>();
	frameInfo.push_back(IDLE_ANIMATION);
	frameInfo.push_back(WALKING_DOWN_ANIMATION);
	frameInfo.push_back(WALKING_UP_ANIMATION);
	frameInfo.push_back(WALKING_LEFT_ANIMATION);
	frameInfo.push_back(WALKING_RIGHT_ANIMATION);
	frameInfo.push_back(CELEBRATE_ANIMATION);
	frameInfo.push_back(CRY_ANIMATION);
	AnimData animData{ texture, frameInfo, frameInfo.size() };

	auto newProblemSolver_ptr = std::make_shared<ProblemSolver>(*(new ProblemSolver()));
	newProblemSolver_ptr->initialize(animData, 0, sf::Vector2f(CHARACTER_START_X * TILESIZE, CHARACTER_START_Y * TILESIZE));

	return newProblemSolver_ptr;
}

std::shared_ptr<Maze> createEmptyMaze() {
	// Create map
	std::vector<int> map(MAP_WIDTH * MAP_HEIGHT, 0);
	MapData mapData{ sf::Vector2u(TILESIZE, TILESIZE), map, MAP_WIDTH, MAP_HEIGHT };

	// Create maze
	auto newMaze_ptr = std::make_shared<Maze>(Maze());
	newMaze_ptr->initialize(TILESET_TEXTURE_FILE, mapData);

	return newMaze_ptr;
}

int main() {
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pathfinder", sf::Style::Close);

	// Create provider for worldState and add to WorldState-Service-Locator 
	WorldStateProvider* worldState = new WorldStateProvider();
	WorldStateLocator::provide(worldState);

	// Set window of worldState
	worldState->addWindow(window);

	// Create Map
	auto maze = createEmptyMaze();
	worldState->addNewObject({ MAP_NAME, -1 }, maze, true, false);

	// Create Character
	auto problemSolver = createProblemSolver();
	worldState->addNewObject({ AI_CHARACTER_NAME, 10 }, problemSolver, true, true);

	// create clock to keep track of frame deltas. 
	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Restart clock and get the time passed since last frame. 
		sf::Time deltaTime = clock.restart();
		// Clear all drawn objects from previous frame
		window.clear();

		// Update Objects
		for (auto obj_ptr : worldState->getUpdatables()) {
			obj_ptr.second->update(deltaTime.asSeconds());
		}

		// Render Objects
		for (auto obj_ptr : worldState->getDrawables()) {
			obj_ptr.second->draw(window);
		}

		window.display();
	}

	return 0;
}