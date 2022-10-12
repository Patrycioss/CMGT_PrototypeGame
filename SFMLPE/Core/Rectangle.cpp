#include "Rectangle.hpp"


////////////////////////////////////////////////////////////////////////////////////////////
Rectangle::Rectangle(const sf::Vector2f& position, const sf::Vector2f& size)
	: position_(position)
	, size_(size)
	{};

Rectangle::Rectangle(const sf::Vector2f& position, const float& width, const float& height)
	: position_(position)
	, size_(sf::Vector2f{width,height})
	{};

Rectangle::Rectangle(const float& x, const float& y, const sf::Vector2f& size)
	: position_(sf::Vector2f{x,y})
	, size_(size)
	{};

Rectangle::Rectangle(const float& x, const float& y, const float& width, const float& height)
	: position_(sf::Vector2f{(float)x,(float)y})
	, size_(sf::Vector2f{width,height})
	{};

Rectangle::Rectangle(const sf::Vector2f& position)
	: position_(position)
	, size_(sf::Vector2f{0,0})
	{};

Rectangle::Rectangle(const float& x, const float& y)
	: position_(sf::Vector2f{x,y})
	, size_(sf::Vector2f{0,0})
	{};

Rectangle::Rectangle()
	: position_(sf::Vector2f{0,0})
	, size_(sf::Vector2f{0,0})
{};

////////////////////////////////////////////////////////////////////////////////////////////

void Rectangle::MoveX(const float& amount){
	position_.x += amount;
};

void Rectangle::MoveY(const float& amount){
	position_.y += amount;
};

void Rectangle::Move(const float& x, const float& y){
	position_ += sf::Vector2f{x,y};
};

void Rectangle::Move(const sf::Vector2f& vector2){
	position_ += vector2;
};

////////////////////////////////////////////////////////////////////////////////////////////

float Rectangle::left() const{
	return position_.x;
};

float Rectangle::right() const {
	return position_.x + size_.x;
};

float Rectangle::top() const {
	return position_.y;
};

float Rectangle::bottom() const {
	return position_.y + size_.y;
};

////////////////////////////////////////////////////////////////////////////////////////////
