#pragma once
#include "Sprite.hpp"


class AnimationSprite : public Sprite
{
private:
	sf::Clock clock;

	unsigned int frameWidth_;
	unsigned int frameHeight_;

	unsigned int rows_;
	unsigned int columns_;

	unsigned int startFrame_ = 0;
	unsigned int currentFrame_ = 0;

	unsigned int frameCount_;
	unsigned int cycleFrameCount_;

	//Frame delay in milliseconds
	unsigned int animationDelay_ = 100;




public:

	//Frames index from 0
	void SetFrame(const unsigned int& frame);

	void SetCycle(const unsigned int& startFrame, const unsigned int& numFrames,
	              const unsigned int& animationDelay = 0, const bool& setFrame = true);

	void SetDelay(const unsigned int& animationDelay);

	AnimationSprite();

	AnimationSprite(const sf::Vector2f& position,
	                const char* path, const unsigned int& numFrames,
	                const unsigned int& columns, const unsigned int& rows,
	                const bool& visible = true);

//	  AnimationSprite(const sf::Vector2f& position, const sf::Vector2f& size);

	void Animate();

	void Render(sf::RenderWindow& window) override;

	void UpdateSize() override;

	const unsigned int& startFrame() const;
	const unsigned int& currentFrame() const;
	const unsigned int& cycleLength() const;
};