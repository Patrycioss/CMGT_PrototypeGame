#include "TestSprite.hpp"

TestSprite::TestSprite(const sf::Vector2f& position) : SFMLPE::Sprite("test.png", position)
{
	
}

void TestSprite::Update() {
}

void TestSprite::Start() {
	
}

TestSprite::~TestSprite() {
	printf("Goodbye cruel world :(");

}
