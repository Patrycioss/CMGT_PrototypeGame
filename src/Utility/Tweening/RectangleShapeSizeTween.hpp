#pragma once
#include "Tween.hpp"

class RectangleShapeSizeTween : public Tween
{
private:
	sf::Vector2f targetSize_;
	sf::Vector2f sizeDifference_;
	sf::Vector2f originalSize_;
	sf::RectangleShape& rectangleShape_;
	
public:
	RectangleShapeSizeTween(sf::RectangleShape& rectangleShape, const sf::Vector2f& targetSize, const sf::Time& duration);
	void Update() override;
};
