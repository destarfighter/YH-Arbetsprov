#pragma once
#include "WorldState.hpp"

#define AICOMMONLIBRARY_API __declspec(dllexport)

class AICOMMONLIBRARY_API WorldStateLocator {
public:
	static WorldState* getWorldState();

	static void provide(WorldState* service);

private:
	static WorldState* service_;
};
