#pragma once
#include "../SFMLPE/SFMLPE.hpp"

class TestSprite : public SFP::Sprite
{
public:
	explicit TestSprite(const sf::Vector2f& position);
	void Start() override;
	void Update() override;
	
	~TestSprite();
};