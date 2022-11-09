#include "SpritePosTween.hpp"
#include "TweenManager.hpp"

SpritePosTween::SpritePosTween(Sprite* sprite, const sf::Vector2f& targetPosition, const sf::Time& duration) 
	: sprite_(sprite), originalPosition_(sprite->position()), targetPosition_(targetPosition)
{
	locationDifference_ = targetPosition_ - originalPosition_;
	totalDuration_ = duration;
}

void SpritePosTween::Update() {
	sf::Time time = coolDownTimer_.getElapsedTime();

	if (time.asSeconds() >= totalDuration_.asSeconds())
	{
		sprite_->SetPosition(targetPosition_);
		Finish();
		return;
	}

	float divisor = totalDuration_.asSeconds()/time.asSeconds();

	sf::Vector2f newPosition = originalPosition_ + (locationDifference_ / divisor);
	sprite_->SetPosition(newPosition);
}
