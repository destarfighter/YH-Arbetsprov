#pragma once
#include <SFML/Graphics.hpp>
#include "WorldObject.h"

struct AnimFrameData {
	// The offset of the first frame and the size of the images of an animation
	sf::Rect<int> animOffset_;
	// The total number of frames for said animation
	unsigned int numFrames_;
	// The name of the animation
	std::string animName_;
};

struct AnimData {
	// ImageFile with all the animations
	std::shared_ptr<sf::Texture> spriteSheet_ptr_;
	// The frame data for all the different animations
	std::vector<AnimFrameData> frameInfo_;
	// The number of different animations
	unsigned int numOfAnimatons_;
};

class AnimatedSprite : public sf::Sprite {
private:
	// Mapping for animation states in the AnimatedSprite, name of animation - index of animation in AnimData
	std::map<std::string, int> animationStates_;
	// All of the animation data (includes ImageFile and FrameData)
	AnimData animData_;
	// The particular animation that is active
	unsigned int animNum_;
	// The frame number of the active animation that's being displayed
	unsigned int frameNum_;
	// Anmount of time the current frame has been displayed
	float frameTime_;
	// The FPS the animation is running at
	float animFPS_;

public:
	AnimatedSprite();
	virtual void initialize(AnimData animData, unsigned int startingAnimNum);
	virtual void update(float deltaTime);
	void changeAnim(unsigned int num);
	int getAnimationIndexByName(std::string animationName);
};