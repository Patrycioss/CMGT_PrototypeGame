#pragma once


#include "Tween.hpp"
#include "../../Engine/Sprite.hpp"

class SpritePosTween : public Tween
{
private:
	sf::Vector2f targetPosition_;
	sf::Vector2f locationDifference_;
	sf::Vector2f originalPosition_;
	Sprite* sprite_;

public:
	SpritePosTween(Sprite* sprite, const sf::Vector2f& targetPosition, const sf::Time& duration);
	void Update() override;
};
