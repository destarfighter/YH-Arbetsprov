#pragma once

#define AICOMMONLIBRARY_API __declspec(dllexport)

// Forward declaration
class AICOMMONLIBRARY_API AIController;

class AICOMMONLIBRARY_API AIState {
protected:
	AIController* parent_;
public: 
	~AIState();
	AIState(AIController* parent);
	virtual void update(float deltaTime);
	virtual void enter();
	virtual void exit();
};

