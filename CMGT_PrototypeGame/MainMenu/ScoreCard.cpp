#include "ScoreCard.hpp"

ScoreCard::ScoreCard(const sf::Vector2f& position)
	: SFP::GameObject(position)
{
	for (auto & text : text_)
	{
		text.setFont(*SFP::ResourceManager::LoadFont("fonts/minecraftFont.ttf"));
		text.setCharacterSize(20);
		text.setStyle(sf::Text::Regular);
		text.setFillColor(sf::Color::Red);
	}
	
	text_[0].setPosition({position.x + 50, position.y + 68});
	text_[1].setPosition({position.x + 190, position.y + 68});
	text_[2].setPosition({position.x + 300, position.y + 68});
}

ScoreCard::ScoreCard(const sf::Vector2f& position, const Score& score) 
	: ScoreCard(position)
{
	score_ = score;
	
	text_[0].setString(score.name);
	text_[1].setString(std::to_string(score.enemiesSlain));
	text_[2].setString(std::to_string(score.damageDone));
}

const Score& ScoreCard::score() {
	return score_;
}

void ScoreCard::Render(sf::RenderWindow& window) 
{
	SFP::GameObject::Render(window);
	
	for (const sf::Text& text : text_)
		window.draw(text);
}
