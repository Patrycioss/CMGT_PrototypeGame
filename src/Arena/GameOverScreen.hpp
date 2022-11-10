#pragma once


#include "../Engine/GameObject.hpp"
#include "../UserData/ScoreLoader.hpp"
#include "../Engine/Button.hpp"

class GameOverScreen : public GameObject
{
private:
	sf::RectangleShape greyOverlay_;
	
	std::unique_ptr<Button> exitButton_;
	
	sf::Text score_[2];
	sf::Text gameOver_;
	
	
public:
	explicit GameOverScreen(const Score& score);
	
	void Render(sf::RenderWindow& window) override;
};
