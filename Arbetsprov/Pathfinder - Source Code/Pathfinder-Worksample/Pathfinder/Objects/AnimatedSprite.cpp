#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite()
: sf::Sprite()
, animationStates_(std::map<std::string, int>())
, animData_(AnimData())
, animNum_(0)
, frameNum_(0)
, frameTime_(0)
, animFPS_(12) { } // TODO: add frame rate as argument, or set-function

void AnimatedSprite::initialize(AnimData animData, unsigned int startingAnimNum) {
		animData_ = animData;
		animNum_ = startingAnimNum;
		sf::Sprite::setTexture(*animData_.spriteSheet_ptr_);
		// Set animation to default animation.
		changeAnim(0);
		// Create Animation States Mappings
		for (unsigned int i = 0; i < animData.numOfAnimatons_; ++i) {
			animationStates_.emplace(animData.frameInfo_[i].animName_, i);
		}
}

void AnimatedSprite::update(float deltaTime) {
	// Update how long the current frame has been displayed
	frameTime_ += deltaTime;
	// This check determines if it's time to change to the next frame.
	if (frameTime_ > (1 / animFPS_)) {
		// The number of frames to increment is the integral result of
		// FrameTime / (1 / animFPS), which is frameTime * animFPS
		frameNum_ += frameTime_ * animFPS_;
		// Check if we advanced past the last frame, and must wrap.
		if (frameNum_ >= animData_.frameInfo_[animNum_].numFrames_) {
			// The modulus (%) makes sure we wrap correctly.
			frameNum_ = frameNum_ % animData_.frameInfo_[animNum_].numFrames_;
		}

		// Update the active sprite with current frame.
		sf::Sprite::setTextureRect(sf::IntRect(
			animData_.frameInfo_[animNum_].animOffset_.left 
				+ animData_.frameInfo_[animNum_].animOffset_.width * frameNum_,
			animData_.frameInfo_[animNum_].animOffset_.top,
			animData_.frameInfo_[animNum_].animOffset_.width,
			animData_.frameInfo_[animNum_].animOffset_.height));

		// The modulus (%) makes sure we wrap FPS correctly. 
		frameTime_ = std::fmod(frameTime_, 1 / animFPS_);
	}
}

void AnimatedSprite::changeAnim(unsigned int num) {
	if (num > animData_.numOfAnimatons_)
		throw std::exception("Animation number out of range.");

	// The active animation is now at frame 0 and 0.0f time
	animNum_ = num;
	frameNum_ = 0;
	frameTime_ = 0.0f;

	// Set active sprite, which is just the starting frame.
	sf::Sprite::setTextureRect(sf::IntRect(
		animData_.frameInfo_[animNum_].animOffset_.left,
		animData_.frameInfo_[animNum_].animOffset_.top,
		animData_.frameInfo_[animNum_].animOffset_.width,
		animData_.frameInfo_[animNum_].animOffset_.height));

	// Update Animation origin based on TileSize
	int xOffset = std::abs(32 - animData_.frameInfo_[animNum_].animOffset_.width); // TODO: add tilesize '32' as argument
	int yOffset = std::abs(32 - animData_.frameInfo_[animNum_].animOffset_.height);
	// apply to origin
	sf::Sprite::setOrigin(xOffset, yOffset);
}

int AnimatedSprite::getAnimationIndexByName(std::string animationName)
{
	if (animationStates_.find(animationName) != animationStates_.end()) {
		return animationStates_[animationName];
	}
	throw std::exception("There is no key 'name' in animationStates");
}
