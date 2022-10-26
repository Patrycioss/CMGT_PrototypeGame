#include "ScoreCard.hpp"

ScoreCard::ScoreCard(const sf::Vector2f& position) 
	: SFMLPE::Sprite("scoreCard.png", position)
{
	
	if (!font_.loadFromFile("fonts/minecraftFont.ttf")) 
		printf("Couldn't load font with path fonts/minecraftFont.tff :( \n");
	
	text_.setFont(font_);
	text_.setCharacterSize(100);
	text_.setStyle(sf::Text::Regular);
	text_.setFillColor(sf::Color::Red);
}

ScoreCard::ScoreCard(const sf::Vector2f& position, const Score& score) 
	: ScoreCard(position)
{
	score_ = score;
	
	text_.setString(score.name + " has slain " + std::to_string(score.enemiesSlain) + " enemies and dealt " + std::to_string(score.damageDone) + " damage!");
}

const Score& ScoreCard::score() {
	return score_;
}

void ScoreCard::Render(sf::RenderWindow& window) 
{
	//miss render voor maken van text
	SFMLPE::Sprite::Render(window);
	window.draw(text_);

}
