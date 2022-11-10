#pragma once
#include "../Character/Character.hpp"
#include "../Engine/Button.hpp"
#include "OutputLog.hpp"
#include "../Engine/Scene.hpp"
#include "../Engine/AnimationSprite.hpp"
#include "SFML/Audio/Sound.hpp"
#include "../UserData/SaveLoader.hpp"
#include "GameOverScreen.hpp"

class CMGT_PrototypeGame;

class Arena : public Scene
{
private:
	bool playerTurn_;
	Character player_;
	Character opponent_;
	
	bool defeated;
	
	Difficulty difficulty_;
	
	unsigned int enemiesSlain_;
	
	CMGT_PrototypeGame& game_;
	
	static const sf::Vector2f FULL_WELLNESS_BAR_SIZE;
	
//Arena creation

	sf::RectangleShape background_;
	sf::RectangleShape textBox_;
	OutputLog outputLog_;
	
	std::unique_ptr<Button> exitButton_;
	
	//attack-prepare-recover-castMagic
	std::unique_ptr<Button> moveButtons_[4];
	
	std::unique_ptr<AnimationSprite> playerAvatar_;
	
	std::unique_ptr<AnimationSprite> restorationEffect_;
	std::unique_ptr<AnimationSprite> preparationEffect_;
	std::unique_ptr<AnimationSprite> magicEffect_;
	
	sf::Text dispAttributes_[12];
	sf::RectangleShape attribRects_[2];
	void MakeDispAttributes();
	
	
	std::unique_ptr<AnimationSprite> opponentAvatar_;
	
	sf::RectangleShape nameBoxes_[2];
	sf::Text nameTexts_[2];
	void MakeNameTags();
	
	
	void CreateArena();
	void CreateMoveButtons();
	void CreateWellnessBars();
	
	void MakePlayerAvatar();
	void MakeOpponentAvatar();
	
	void GenerateNewOpponent();
	
	sf::RectangleShape wellnessBars_[8];
	
	bool opponentHealthDone_, opponentSanityDone_, playerHealthDone_, playerSanityDone_;
	
	//Sound
	sf::Sound magicSound_;
	sf::Sound attackSound_;
	sf::Sound prepAndRecoverSound_;
	sf::Sound prepareSound_;
	sf::Sound trembleSound_;
	sf::Sound victorySound_;
	sf::Sound defeatSound_;
	
	std::unique_ptr<GameOverScreen> gameOverScreen_;
	
	

public:
	explicit Arena(CMGT_PrototypeGame& game);
	
	void Begin(const sf::String& string, const Avatar& avatar, Attributes& attributes, const Difficulty& difficulty);
	void Continue(const SaveInformation& saveInformation);
	
	void EndPlayerTurn();
	void Render(sf::RenderWindow& window) override;
	
	void Save();
	
	void CreateExitButton();
	void UpdateInformationDisplay();
	void EndOpponentTurn();
	void GenerateOpponentTurn();
	void DecideTurn();
	void UpdateWellnessBars(const std::function<void()>& function = [](){});
	void GenericStuff();
	void LockMoveButtons(const bool& lock);
	void Defeat();
};
