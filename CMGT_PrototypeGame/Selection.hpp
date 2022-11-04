#pragma once
#include "../SFMLPE/SFMLPE.hpp"
#include "Button.hpp"
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
	std::unique_ptr<Button> choiceButtons_[3];
	
	Button* selectedAvatarButton_ = nullptr;
	Avatar selectedAvatar_ = Avatar(0);
	void SelectAvatar(Button* button, const Avatar& avatar);

//Name Creation
	sf::Text chooseYourName_;
	std::unique_ptr<TextInput> nameInput_;

	sf::Text maxCharactersWarning_;
	bool maxCharactersReached_ = false;
	sf::Clock maxCharacterFadeClock_;
	
//Point distribution
	Attributes chosenAttributes_;
	unsigned int pointsToSpend_ = 6;
	
	std::unique_ptr<Button> pointButtons_[6];
	std::unique_ptr<Button> randomizer_;
	sf::Text stats_[6];
	sf::Text pointsToSpendText_[2];
	
	void UpdatePoints();
	void StartGame();
	
//Difficulty selection
	Difficulty difficulty_;
	std::unique_ptr<Button> difficultyButtons_[2];
	
//Start Game
	std::unique_ptr<Button> startButton_;
	
	std::unique_ptr<Button> exitButton_;

public:
	explicit Selection(CMGT_PrototypeGame& game);
	
	void Update() override;
	void Render(sf::RenderWindow& window) override;
	void CreateExitButton();
};