#pragma once
#include "SFML/System/Vector2.hpp"


template <typename T>
struct Rectangle
{
	sf::Vector2<T> position;
	sf::Vector2<T> size;
	
	constexpr Rectangle(const sf::Vector2<T>& position, const sf::Vector2<T>& size)
		: position(position), size(size){};
	
	constexpr explicit Rectangle(const sf::Vector2<T>& position)
		: position(position), size({0,0}){};
	
	constexpr void Move(const sf::Vector2<T>& vector2) {
		position += vector2;
	};
};
