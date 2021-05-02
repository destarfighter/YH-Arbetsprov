#pragma once
#include <SFML/Graphics.hpp>

#define AICOMMONLIBRARY_API __declspec(dllexport)

struct AICOMMONLIBRARY_API WorldObjectIdentifier {
	std::string name_;
	int priority_{0};

	friend bool operator==(const WorldObjectIdentifier& lhs, const WorldObjectIdentifier& rhs) {
		return lhs.name_ == rhs.name_;
	}
	friend bool operator<(const WorldObjectIdentifier& lhs, const WorldObjectIdentifier& rhs) {
		if (rhs.priority_ == lhs.priority_) {
			return lhs.name_ < rhs.name_;
		}
		else {
			return lhs.priority_ < rhs.priority_;
		}
	}
};

class AICOMMONLIBRARY_API WorldObject {
public:
	virtual void update(float deltaTime);
	virtual void draw(sf::RenderWindow& window);
};