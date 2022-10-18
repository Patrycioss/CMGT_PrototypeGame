#pragma once
#include "SFML/System/Vector2.hpp"

struct Rectangle
{
	sf::Vector2f position_;
	sf::Vector2f size_;
	
	Rectangle(const sf::Vector2f& position, const sf::Vector2f& size);
	Rectangle(const sf::Vector2f& position, const float& width, const float& height);
	
	Rectangle(const float& x, const float& y, const sf::Vector2f& size);
	Rectangle(const float& x, const float& y, const float& width, const float& height);
	
	explicit Rectangle(const sf::Vector2f& position);
	Rectangle(const float& x, const float& y);
	
	Rectangle();
	
	void MoveX(const float& amount);
	void MoveY(const float& amount);
	void Move(const float& x, const float& y);
	void Move(const sf::Vector2f& vector2);
	
	[[nodiscard]] float left() const;
	[[nodiscard]] float right() const;
	[[nodiscard]] float top() const;
	[[nodiscard]] float bottom() const;
};