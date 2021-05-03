#include "WorldStateLocator.h"

WorldState* WorldStateLocator::getWorldState() { return service_; };

void WorldStateLocator::provide(WorldState* service) {
	service_ = service;
}

WorldState* WorldStateLocator::service_;
