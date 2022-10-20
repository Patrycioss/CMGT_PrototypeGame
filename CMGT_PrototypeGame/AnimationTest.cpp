#include "AnimationTest.hpp"

AnimationTest::AnimationTest(const sf::Vector2f& position)
		: SFMLPE::AnimationSprite(position, "testSheet.png", 11, 1, 11){}

void AnimationTest::Start() {
}
