#include "RectPosTween.hpp"

void RectPosTween::Update()
{
	if (rectangleShape_ == nullptr)
	{
		Abort();
		return;
	}
	
	sf::Time time = coolDownTimer_.getElapsedTime();

	if (time.asSeconds() >= totalDuration_.asSeconds())
	{
		rectangleShape_->setPosition(targetPosition_);
		Finish();
		return;
	}

	float divisor = totalDuration_.asSeconds()/time.asSeconds();

	sf::Vector2f newPosition = originalPosition_ + (locationDifference_ / divisor);
	rectangleShape_->setPosition(newPosition);
}

RectPosTween::RectPosTween(sf::RectangleShape& rectangleShape, const sf::Vector2f& targetPosition, const sf::Time& duration)
	: targetPosition_(targetPosition), rectangleShape_(&rectangleShape), originalPosition_(rectangleShape.getPosition())
{
	locationDifference_ = targetPosition_ - originalPosition_;
	totalDuration_ = duration;
}
