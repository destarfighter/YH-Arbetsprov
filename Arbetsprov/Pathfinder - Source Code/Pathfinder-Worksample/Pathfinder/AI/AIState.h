#pragma once

// Forward declaration
class AIController;

/// <summary>
/// A Base-State for all states managed through a AIController
/// </summary>
class AIState {
protected:
	AIController* parent_;
public: 
	~AIState();
	AIState(AIController* parent);
	virtual void update(float deltaTime);
	virtual void enter();
	virtual void exit();
};

