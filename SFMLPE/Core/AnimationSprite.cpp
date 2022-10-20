#include "AnimationSprite.hpp"

SFMLPE::AnimationSprite::AnimationSprite
		(const sf::Vector2f& position,
		 const char* path, const unsigned int& numFrames,
		 const unsigned int& rows, const unsigned int& columns,
		 const bool& visible)
		: Sprite(path, position, visible)
		, rows_(rows), columns_(columns)
		, frameCount_(numFrames), cycleFrameCount_(numFrames)
{
	frameWidth_ = texture_->getSize().x / columns;
	frameHeight_ = texture_->getSize().y / rows;
	UpdateSize();
	SetFrame(0);
}

SFMLPE::AnimationSprite::AnimationSprite
		(const sf::Vector2f& position,
		 sf::Texture* texture, const unsigned int& numFrames,
		 const unsigned int& rows, const unsigned int& columns,
		 const bool& visible)
		: Sprite(texture, position, visible)
		, rows_(rows), columns_(columns)
		, frameCount_(numFrames), cycleFrameCount_(numFrames)
{
	frameWidth_ = texture_->getSize().x / columns;
	frameHeight_ = texture_->getSize().y / rows;
	UpdateSize();
	SetFrame(0);
}


void SFMLPE::AnimationSprite::Animate()
{
//	printf("CurrentFrame: %u, ElapsedTime: %u, Delay: %u \n",
//	       currentFrame_, clock.getElapsedTime().asMilliseconds(), animationDelay_);
	
	if (clock.getElapsedTime().asMilliseconds() >= animationDelay_)
	{
		currentFrame_++;

		if (currentFrame_ >= cycleFrameCount_ + startFrame_) currentFrame_ = startFrame_;
		
		SetFrame(currentFrame_);
		
		clock.restart();
	}
}

void SFMLPE::AnimationSprite::SetFrame(const unsigned int& frame) 
{
	if (frame >= frameCount_) {
		printf("Frame %u is out of bounds in SetFrame() for animationSprite with ID: %u!", frame, ID());
		return;
	}
	
	if (frame == 0)
	{
		sprite_.setTextureRect(
				sf::Rect<int>(
						sf::Vector2i(0,0),
						sf::Vector2i((int) frameWidth_, (int) frameHeight_)));
	}
	else if (rows_ == 1) {
		sprite_.setTextureRect(
				sf::Rect<int>(
						sf::Vector2i((int) (frameWidth_ * frame), 0),
						sf::Vector2i((int) frameWidth_, (int) frameHeight_)));
	}
	else if (columns_ == 1)
	{
		sprite_.setTextureRect(
				sf::Rect<int>(
						sf::Vector2i(0, (int) (frameHeight_ * frame)),
						sf::Vector2i((int) frameWidth_, (int) frameHeight_)));
	}
	else 
	{
		sf::Vector2i position{0,0};
		
		for (int i = 0; i < frame; i++)
		{
			position.x += (int) frameWidth_;
			
			if (i * frameWidth_ == texture_->getSize().x){
				position.x = 0;
				position.y += (int) frameHeight_;
			}
		}

		sprite_.setTextureRect(sf::Rect<int>(position,sf::Vector2i((int) frameWidth_, (int) frameHeight_)));
	}
}

void SFMLPE::AnimationSprite::SetCycle
(const unsigned int& startFrame, const unsigned int& numFrames, 
 const unsigned int& animationDelay, const bool&setFrame)
{
	startFrame_ = startFrame;
	cycleFrameCount_ = numFrames;
	
	if (setFrame) SetFrame(startFrame);
}

void SFMLPE::AnimationSprite::UpdateSize() 
{
	GameObject::UpdateSize((float) frameWidth_, (float) frameHeight_);
}

