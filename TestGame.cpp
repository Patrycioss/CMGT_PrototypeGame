#include "TestGame.hpp"
#include "TestSprite.hpp"

#define isKeyPressed sf::Keyboard::isKeyPressed

TestGame::TestGame() : SFMLPE::Game(){} // NOLINT(cppcoreguidelines-pro-type-member-init)

void TestGame::Start()
{
	
	a = new TestSprite(sf::Vector2f(0,0));
	b = new SFMLPE::Sprite("head.png", sf::Vector2f(0,0));

	a->AddChild(b);
	AddScene("test").AddChild(a);
}

sf::Vector2f get_wasd_direction()
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

sf::Vector2f get_arrows_direction()
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


void TestGame::Update() {
	a->Move(get_wasd_direction() * speed);
	b->Move(get_arrows_direction() * speed);
}




