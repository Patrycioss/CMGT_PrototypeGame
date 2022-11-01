#pragma once
#include "../ScoreManager.hpp"
#include "../../SFMLPE/SFMLPE.hpp"

class ScoreCard : public SFP::GameObject
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


