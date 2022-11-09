#pragma once

#include "Tween.hpp"

class RectPosTween : public Tween
{
private:
	sf::Vector2f targetPosition_;
	sf::Vector2f locationDifference_;
	sf::Vector2f originalPosition_;
	sf::RectangleShape* rectangleShape_;

public:
	RectPosTween(sf::RectangleShape& rectangleShape, const sf::Vector2f& targetPosition, const sf::Time& duration);
	void Update() override;
};
