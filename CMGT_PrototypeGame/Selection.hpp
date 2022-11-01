#pragma once
#include "../SFMLPE/SFMLPE.hpp"
#include "NewButton.hpp"
#include "Fighting/Character.hpp"
#include "TextInput.hpp"

class CMGT_PrototypeGame;

class Selection : public SFP::Scene
{   
private:
	CMGT_PrototypeGame& game_;

	sf::RectangleShape background_;

	void MakeAvatarSelection();
	void MakeNameCreation();
	void MakePointDistributionStuff();
	void MakeDifficultySelection();
	void MakeStartButton();
	
//Avatar choosing	
	sf::Text chooseYourAvatar_[3];
	std::unique_ptr<SFP::AnimationSprite> choices_[3];
	std::unique_ptr<NewButton> choiceButtons_[3];
	
	NewButton* selectedAvatarButton_ = nullptr;
	void SelectAvatar(NewButton* button);

//Name Creation
	sf::Text chooseYourName_;
	std::unique_ptr<TextInput> nameInput_;

	sf::Text maxCharactersWarning_;
	bool maxCharactersReached_ = false;
	sf::Clock maxCharacterFadeClock_;
	
//Point distribution
	unsigned int pointsToSpend_ = 6;
	unsigned int agilityPoints_ = 0;
	unsigned int strengthPoints_ = 1;
	unsigned int witsPoints_ = 1;
	
	std::unique_ptr<NewButton> pointButtons_[6];
	std::unique_ptr<NewButton> randomizer_;
	sf::Text stats_[6];
	sf::Text pointsToSpendText_[2];
	
	void UpdatePoints();
	void RandomizePoints();
	void StartGame();
	
//Difficulty selection
	Difficulty difficulty_;
	std::unique_ptr<NewButton> difficultyButtons_[2];
	
//Start Game
	std::unique_ptr<NewButton> startButton_;

public:
	explicit Selection(CMGT_PrototypeGame& game);
	
	void Update() override;
	void Render(sf::RenderWindow& window) override;
};