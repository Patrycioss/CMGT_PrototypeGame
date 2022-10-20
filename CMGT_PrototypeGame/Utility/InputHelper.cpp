#include "InputHelper.hpp"
#include "SFML/Window/Keyboard.hpp"
#define isKeyPressed sf::Keyboard::isKeyPressed


sf::Vector2f InputHelper::get_wasd_direction() 
{
	sf::Vector2f direction{0,0};

	if (isKeyPressed(sf::Keyboard::A))
		direction.x--;

	if (isKeyPressed(sf::Keyboard::D))
		direction.x++;

	if (isKeyPressed(sf::Keyboard::W))
		direction.y--;

	if (isKeyPressed(sf::Keyboard::S))
		direction.y++;

	return direction;
}

sf::Vector2f InputHelper::get_arrowKeys_direction() 
{
	sf::Vector2f direction{0,0};

	if (isKeyPressed(sf::Keyboard::Left))
		direction.x--;

	if (isKeyPressed(sf::Keyboard::Right))
		direction.x++;

	if (isKeyPressed(sf::Keyboard::Up))
		direction.y--;

	if (isKeyPressed(sf::Keyboard::Down))
		direction.y++;

	return direction;
}
