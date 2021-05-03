#pragma once
#include "WorldState.hpp"

/// <summary>
/// A service locator to give access to a service that manages all objects that should be updated or drawn.
/// </summary>
class WorldStateLocator {
public:
	static WorldState* getWorldState();

	static void provide(WorldState* service);

private:
	static WorldState* service_;
};
