#include "GameOverScreen.hpp"
#include "../Engine/Game.hpp"
#include "../Engine/ResourceManager.hpp"

GameOverScreen::GameOverScreen(const Score& score) 
	: GameObject(sf::Vector2f{0,0})
{
	greyOverlay_.setSize({1100,400});
	greyOverlay_.setPosition(sf::Vector2f{100,200});
	greyOverlay_.setFillColor(sf::Color{123,123,123,225});
	
	//Name
	std::string scoreString1 = "You have done " + std::to_string(score.damageDone) + " damage to enemies ";
	std::string scoreString2 = "and you have slain " + std::to_string(score.enemiesSlain) + " enemies!";
	score_[0].setString(scoreString1);
	score_[1].setString(scoreString2);
	score_[0].setFillColor(sf::Color::White);
	score_[1].setFillColor(sf::Color::White);
	score_[0].setCharacterSize(40);
	score_[1].setCharacterSize(40);
	score_[0].setFont(*ResourceManager::LoadFont("fonts/minecraftFont.ttf"));
	score_[1].setFont(*ResourceManager::LoadFont("fonts/minecraftFont.ttf"));
	score_[0].setPosition({270,400});
	score_[1].setPosition({320,450});
	
	//GameOver text
	gameOver_.setString("GAME OVER!");
	gameOver_.setFont(*ResourceManager::LoadFont("fonts/minecraftFont.ttf"));
	gameOver_.setCharacterSize(60);
	gameOver_.setFillColor(sf::Color::White);
	gameOver_.setPosition({450,250});
}

void GameOverScreen::Render(sf::RenderWindow& window) {
	window.draw(greyOverlay_);
	window.draw(score_[0]);
	window.draw(score_[1]);
	window.draw(gameOver_);
	
	
	GameObject::Render(window);
}
