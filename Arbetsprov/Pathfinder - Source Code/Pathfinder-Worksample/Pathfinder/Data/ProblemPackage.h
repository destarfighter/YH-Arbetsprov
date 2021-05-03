#pragma once
#include <SFML/System/Vector2.hpp>
#include "MapPackage.h"

/// <summary>
/// A Data package containing the info to describe a pathfinder-problem
/// </summary>
struct ProblemData {
	// The environment of a problem for a pathfinder
	MapData mapData_;
	// The desination of a pathfinder problem
	sf::Vector2u destination_;
};