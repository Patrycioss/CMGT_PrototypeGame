#pragma once
#include "../UserData/ScoreLoader.hpp"
#include "../Engine/GameObject.hpp"

class ScoreCard : public GameObject
{
private:
	Score score_;
	
	sf::Font font_;
	sf::Text text_[3];
	
public:
	explicit ScoreCard(const sf::Vector2f& position);
	ScoreCard(const sf::Vector2f& position, const Score& score);

	const Score& score();
	
	void Render(sf::RenderWindow &window) override;
};


