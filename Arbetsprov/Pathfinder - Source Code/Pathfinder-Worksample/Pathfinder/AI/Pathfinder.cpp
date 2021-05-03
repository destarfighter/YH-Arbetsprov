#include "Pathfinder.h"


bool Pathfinder::isTraversable(const long int prev_pos, const Step& step, MapData mapData)
{
	long int new_index = prev_pos + step.step_value;

	switch (step.direction)
	{
	case UP:
		// out-of-bounds: above
		if (new_index < 0) return false; 
		break;
	case DOWN:
		// out-of-bounds: under
		if (new_index >= mapData.width_ * mapData.height_)  return false; 
		break;
	case LEFT:
		// out-of-bounds: left
		if (new_index % mapData.width_ == mapData.width_ - 1 || new_index < 0)  return false; 
		break;
	case RIGHT:
		// out-of-bounds: right
		if (new_index % mapData.width_ == 0 || new_index >= mapData.height_ * mapData.width_)  return false; 
		break;
	}

	for (auto tile : MAP_WALLS) {
		if (mapData.tiles_[new_index] == tile) {
			// Node is not traversable
			return false; 
		}
	}
	// Node is traversable
	return true; 
}

std::vector<unsigned long int> Pathfinder::makePath(const long int target, const long int start, std::vector<long int>& prev)
{
	std::vector<unsigned long int> path;
	long int current = target;

	// Retrace the path from target back to start-position. 
	while (current != start && current != LONG_MAX)
	{
		path.push_back(current);
		current = prev[current];
	}

	// reverse path
	std::reverse(path.begin(), path.end());
	return path;
}

long int Pathfinder::manhattanDistance(long int position, long int target)
{
	// convert values to coordinates
	int positionX = (position % MAP_WIDTH);
	int positionY = ((position - positionX) / MAP_WIDTH);
	int targetX = (target % MAP_WIDTH);
	int targetY = ((target - targetX) / MAP_WIDTH);

	// subtract position from target and return absolute value of distance
	return (std::abs(targetX - positionX) + std::abs(targetY - positionY));
}

std::vector<unsigned long int> Pathfinder::findPath(sf::Vector2f startPosition, sf::Vector2u destination, MapData mapData) {
	
	std::priority_queue<Position> open_pos_que;
	std::vector<long int> current_position_score(mapData.height_ * mapData.width_, LONG_MAX);
	std::vector<long int> previous_positions(mapData.height_ * mapData.width_, LONG_MAX);

	long int target = (destination.y * mapData.width_) + destination.x;
	long int start = ((startPosition.y / TILESIZE) * mapData.width_) + (startPosition.x / TILESIZE);

	const Step movement_directions[] = { {UP, -static_cast<long int>(mapData.width_)}, {DOWN, mapData.width_}, {LEFT, -1}, {RIGHT, 1} };
	const int step_cost = 1;
	pathWasFound = false;

	// Start position need manhattan distance
	auto start_manhattan = manhattanDistance(start, target);
	open_pos_que.push({ start , 0, start_manhattan, start_manhattan });
	current_position_score[start] = start_manhattan;

	while (!open_pos_que.empty())
	{
		Position current = open_pos_que.top();
		open_pos_que.pop();

		if (current_position_score[current.pos] != current.f) 
			continue; // position is outdated by another route. 

		// Add current index as 'visited' to solution-animation list
		solutionAnimation.push_back({ current.pos, VISITED_TILE });

		if (current.pos == target)
		{
			auto result = makePath(current.pos, start, previous_positions);
			pathWasFound = true;
			return result; // found path from start to target
		}

		for (Step step : movement_directions)
		{
			if (!isTraversable(current.pos, step, mapData)) 
				continue; // Node is not traversable

			long int new_position = current.pos + step.step_value;
			long int new_dist = current.dist + step_cost;
			long int new_h = manhattanDistance(new_position, target);
			long int new_f = new_dist + new_h;

			if (new_f < current_position_score[new_position])
			{
				// Add current index as 'investigated' to solution-animation list
				solutionAnimation.push_back({ new_position, INVESTIGATED_TILE });

				current_position_score[new_position] = new_f;
				previous_positions[new_position] = current.pos;
				open_pos_que.push({new_position, new_dist, new_h, new_f});
			}
		}
	}
	pathWasFound = false;
	return std::vector<unsigned long int>(); // found no path from start to target
}

Pathfinder::Pathfinder()
: pathWasFound(false)
, solutionAnimation(std::vector<TileFrame>()) {}
