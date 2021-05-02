#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <queue>
#include <climits>
#include <future>
#include "../Data/MapPackage.h"
#include "../config.h"
#include "../Objects/PathAnimater.h"

enum Direction {
	UP = 0,
	DOWN = 1,
	LEFT = 2,
	RIGHT = 3
};

struct Step {
	Direction direction;
	long int step_value;
};

struct Position {
	// describes a point in a 2D-grid of "FindPath"- nMapWidth and nMapHeight
	long int pos;  
	// tentative distance from a source to pos combined with manhattan distance from current position to target.
	long int dist; 
	// a heuristic value for the position, in this case manhattan distance from current position to target. 
	long int h;
	// fitness value for position. a combination of dist and h. 
	long int f;

	friend bool operator<(const Position& lhs, const Position& rhs)
	{
		// compare is reversed due to smaller being better
		return lhs.f > rhs.f;
	}
};

class Pathfinder {
private:
	bool foundPath_;
	std::vector<TileFrame> searchProcess_;

	bool isTraversable(const long int prev_pos, const Step& direction, MapData mapData);
	std::vector<unsigned long int> makePath(const long int target, const long int start, std::vector<long int>& prev);
	long int manhattanDistance(long int position, long int target);

public:
	std::vector<unsigned long int> findPath(sf::Vector2f startPosition, sf::Vector2u destination, MapData mapData);
	const bool getFoundPath() const noexcept { return foundPath_; }
	std::vector<TileFrame> getSearchProcess() const noexcept { return searchProcess_; }
	Pathfinder();
};

