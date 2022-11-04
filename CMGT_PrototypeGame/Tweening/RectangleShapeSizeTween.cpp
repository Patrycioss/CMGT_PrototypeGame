#include "RectangleShapeSizeTween.hpp"

void RectangleShapeSizeTween::Update() 
{
	sf::Time time = coolDownTimer_.getElapsedTime();
	
	if (time.asSeconds() >= totalDuration_.asSeconds())
	{
		rectangleShape_.setSize(targetSize_);
		Finish();
		return;
	}
	
	float divisor = totalDuration_.asSeconds() / time.asSeconds();
	
	sf::Vector2f newSize = originalSize_ + (sizeDifference_ / divisor);
	rectangleShape_.setSize(newSize);
}

RectangleShapeSizeTween::RectangleShapeSizeTween
	(sf::RectangleShape& rectangleShape, const sf::Vector2f& targetSize, const sf::Time& duration)
	: targetSize_(targetSize), rectangleShape_(rectangleShape), originalSize_(rectangleShape.getSize())
{
	sizeDifference_ = targetSize_ - originalSize_;
	totalDuration_ = duration;
}
