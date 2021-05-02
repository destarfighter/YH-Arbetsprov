#pragma once
#include <map>
#include <list>
#include "../Objects/WorldObject.h"

class WorldState {
public:
	virtual ~WorldState() { }

	virtual void addNewObject(WorldObjectIdentifier id, std::shared_ptr<WorldObject> obj_ptr, bool isDrawable = false, bool isUpdatable = false) = 0;
	virtual bool removeObject(WorldObjectIdentifier id) = 0;

	virtual std::shared_ptr<WorldObject> getObject(WorldObjectIdentifier id) = 0;
	virtual WorldObjectIdentifier getObjectId(std::string name) = 0;
	virtual std::map<WorldObjectIdentifier, std::shared_ptr<WorldObject>>& getDrawables() = 0;
	virtual std::map<WorldObjectIdentifier, std::shared_ptr<WorldObject>>& getUpdatables() = 0;

	virtual bool findObjectIdByName(std::string name) = 0;
	virtual bool findObjectById(WorldObjectIdentifier id) = 0;

	virtual void addWindow(sf::RenderWindow& applicationWindow) = 0;
	virtual sf::RenderWindow& getWindow() = 0;
};

class WorldStateProvider : public WorldState {
	// All objects that exist in drawables or updatables has their identity in this list. 
	std::list<WorldObjectIdentifier> worldStateContentIdentities;
	// Drawable collection
	std::map<WorldObjectIdentifier, std::shared_ptr<WorldObject>> drawableObjects_;
	// Updatable collection
	std::map<WorldObjectIdentifier, std::shared_ptr<WorldObject>> updatableObjects_;

	// Window of application
	sf::RenderWindow* applicationWindow_;

public:
	~WorldStateProvider() {
		// Iterate through all lists, freeing memory	
	}

	WorldStateProvider()
		: drawableObjects_(std::map<WorldObjectIdentifier, std::shared_ptr<WorldObject>>())
		, updatableObjects_(std::map<WorldObjectIdentifier, std::shared_ptr<WorldObject>>())
		, worldStateContentIdentities(std::list<WorldObjectIdentifier>()) {}

	virtual void addNewObject(WorldObjectIdentifier id, std::shared_ptr<WorldObject> obj_ptr, bool isDrawable = false, bool isUpdatable = false) {
		// Check if key already exist, throw exception if it does. 
		if (drawableObjects_.find(id) != drawableObjects_.end() ||
			updatableObjects_.find(id) != updatableObjects_.end())
			throw std::exception("Key already exist in WorldState.");
		
		// Add object to drawables and updatable objects respectively depending on arguments. 
		if (isDrawable) 
			drawableObjects_.emplace(id, obj_ptr);
		if (isUpdatable) 
			updatableObjects_.emplace(id, obj_ptr);
		if (isDrawable || isUpdatable) 
			worldStateContentIdentities.push_back(id);
	};

	virtual bool removeObject(WorldObjectIdentifier id) {
		if (drawableObjects_.find(id) != drawableObjects_.end() ||
			updatableObjects_.find(id) != updatableObjects_.end()) {

			worldStateContentIdentities.remove(id);

			if (drawableObjects_.find(id) != drawableObjects_.end()) {
				drawableObjects_.erase(id);
			}
			if (updatableObjects_.find(id) != updatableObjects_.end()) {
				updatableObjects_.erase(id);
			}
			return true;
		}
		return false;
	};

	virtual std::shared_ptr<WorldObject> getObject(WorldObjectIdentifier id) {
		// Check both containers for key 'id'
		if (drawableObjects_.find(id) != drawableObjects_.end()) {
			return drawableObjects_[id];
		}
		else if (updatableObjects_.find(id) != updatableObjects_.end()) {
			return updatableObjects_[id];
		}
		// If element with key isnt found. throw exception. 
		throw std::exception("WorldState does not contain key.");
	};

	virtual WorldObjectIdentifier getObjectId(std::string name) {
		WorldObjectIdentifier objId{ "", 0 };
		// try to find objectId by name
		for (auto id : worldStateContentIdentities) {
			if (id.name_ == name) {
				return objId = id;
				break;
			}
		}
		// If key with name isnt found. throw exception. 
		throw std::exception("WorldState does not contain key with name.");
	}

	virtual std::map<WorldObjectIdentifier, std::shared_ptr<WorldObject>>& getDrawables() { return drawableObjects_; };

	virtual std::map<WorldObjectIdentifier, std::shared_ptr<WorldObject>>& getUpdatables() { return updatableObjects_; }

	virtual bool findObjectIdByName(std::string name) {
		for (auto id : worldStateContentIdentities) {
			if (id.name_ == name) {
				return true;
			}
		}
		return false;
	};

	virtual bool findObjectById(WorldObjectIdentifier id) {
		if (drawableObjects_.find(id) == drawableObjects_.end() &&
			updatableObjects_.find(id) == updatableObjects_.end()) {
			return false;
		}
		else {
			return true;
		}
	};

	virtual void addWindow(sf::RenderWindow& applicationWindow) {
		applicationWindow_ = &applicationWindow;
	}

	virtual sf::RenderWindow& getWindow() {
		return *applicationWindow_;
	}
};