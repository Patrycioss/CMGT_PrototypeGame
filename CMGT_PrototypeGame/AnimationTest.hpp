#pragma once
#include "../SFMLPE/SFMLPE.hpp"


class AnimationTest : public SFMLPE::AnimationSprite
{
protected:
	void Start() override;
	
public:
	explicit AnimationTest(const sf::Vector2f& position);
};

