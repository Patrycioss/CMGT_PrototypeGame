#include "AnimationSprite.hpp"

SFP::AnimationSprite::AnimationSprite
		(const sf::Vector2f& position,
		 const char* path, const unsigned int& numFrames,
		 const unsigned int& columns, const unsigned int& rows, 
		 const bool& visible)
		: Sprite(path, position, visible)
		, rows_(rows), columns_(columns)
		, frameCount_(numFrames)
{
	frameWidth_ = texture_->getSize().x / columns;
	frameHeight_ = texture_->getSize().y / rows;
	UpdateSize();
	SetCycle(1,numFrames);
}

SFP::AnimationSprite::AnimationSprite() 
	: Sprite() 
	, frameWidth_(0)
	, frameHeight_(0)
	, frameCount_(0)
	, currentFrame_(0)
	, rows_(0)
	, columns_(0)
	, cycleFrameCount_(0)
	{}

void SFP::AnimationSprite::Animate()
{
	if (startFrame_ == 0) printf("ID: %u is 0 \n", ID());
	if (cycleFrameCount_ == 1) return;

	if (clock.getElapsedTime().asMilliseconds() >= animationDelay_)
	{
		currentFrame_++;

		if (currentFrame_ >= cycleFrameCount_ + startFrame_) currentFrame_ = startFrame_;
		
		SetFrame(currentFrame_);
		
		clock.restart();
	}
}

void SFP::AnimationSprite::SetFrame(const unsigned int& frame) 
{
	
	if (frame > frameCount_) {  
		printf("Frame %u is out of bounds in SetFrame() for animationSprite_ with ID: %u! \n", frame, ID());
		return;
	}
	
	sf::Vector2i position{0,0};


	for (int i = 0; i < frame - 1; i++) {
		position.x += (int) frameWidth_;

		if (i * frameWidth_ == texture_->getSize().x) {
			position.x = 0;
			position.y += (int) frameHeight_;
		}
	}

	sprite_.setTextureRect(sf::Rect<int>(position,sf::Vector2i((int) frameWidth_, (int) frameHeight_)));

}

void SFP::AnimationSprite::SetCycle
(const unsigned int& startFrame, const unsigned int& numFrames, 
 const unsigned int& animationDelay, const bool&setFrame)
{
	startFrame_ = startFrame;
	cycleFrameCount_ = numFrames;
	
	if (animationDelay != 0) animationDelay_ = animationDelay;
	
	if (setFrame)
	{
		currentFrame_ = startFrame;
		SetFrame(currentFrame_);
	}
	
}

void SFP::AnimationSprite::UpdateSize() 
{
	GameObject::UpdateSize((float) frameWidth_, (float) frameHeight_);
}

const unsigned int& SFP::AnimationSprite::startFrame() const {
	return startFrame_;
}

const unsigned int& SFP::AnimationSprite::currentFrame() const {
	return currentFrame_;
}

const unsigned int& SFP::AnimationSprite::cycleLength() const {
	return cycleFrameCount_;
}

void SFP::AnimationSprite::SetDelay(const unsigned int& animationDelay) 
{
	animationDelay_ = animationDelay;
}

void SFP::AnimationSprite::Render(sf::RenderWindow& window) {
	Animate();
	Sprite::Render(window);
}



