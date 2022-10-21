#include "Rectangle.hpp"


////////////////////////////////////////////////////////////////////////////////////////////
Rectangle::Rectangle(const sf::Vector2f& position, const sf::Vector2f& size)
	: position(position)
	, size(size)
	{};

Rectangle::Rectangle(const sf::Vector2f& position, const float& width, const float& height)
	: position(position)
	, size(sf::Vector2f{width,height})
	{};

Rectangle::Rectangle(const float& x, const float& y, const sf::Vector2f& size)
	: position(sf::Vector2f{x,y})
	, size(size)
	{};

Rectangle::Rectangle(const float& x, const float& y, const float& width, const float& height)
	: position(sf::Vector2f{(float)x,(float)y})
	, size(sf::Vector2f{width,height})
	{};

Rectangle::Rectangle(const sf::Vector2f& position)
	: position(position)
	, size(sf::Vector2f{0,0})
	{};

Rectangle::Rectangle(const float& x, const float& y)
	: position(sf::Vector2f{x,y})
	, size(sf::Vector2f{0,0})
	{};

Rectangle::Rectangle()
	: position(sf::Vector2f{0,0})
	, size(sf::Vector2f{0,0})
{};

////////////////////////////////////////////////////////////////////////////////////////////

void Rectangle::MoveX(const float& amount){
	position.x += amount;
};

void Rectangle::MoveY(const float& amount){
	position.y += amount;
};

void Rectangle::Move(const float& x, const float& y){
	position += sf::Vector2f{x,y};
};

void Rectangle::Move(const sf::Vector2f& vector2){
	position += vector2;
};

////////////////////////////////////////////////////////////////////////////////////////////

float Rectangle::left() const{
	return position.x;
};

float Rectangle::right() const {
	return position.x + size.x;
};

float Rectangle::top() const {
	return position.y;
};

float Rectangle::bottom() const {
	return position.y + size.y;
};

////////////////////////////////////////////////////////////////////////////////////////////
