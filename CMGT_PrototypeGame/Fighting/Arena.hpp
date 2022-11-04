#pragma once
#include "Character.hpp"
#include "../Button.hpp"
#include "../../SFMLPE/SFMLPE.hpp"
#include "../Tweening/RectangleShapeSizeTween.hpp"

class CMGT_PrototypeGame;

class Arena : public SFP::Scene
{
private:
	bool playerTurn_ = true;
	
	Character player_;
	Character opponent_;
	
	Difficulty difficulty_;
	
	unsigned int enemiesSlain_;
	unsigned int damageDone_;
	
	CMGT_PrototypeGame& game_;
	
//Arena creation

	sf::RectangleShape background_;
	sf::RectangleShape textBox_;
	
	std::unique_ptr<Button> exitButton_;
	
	//attack-prepare-recover-castMagic
	std::unique_ptr<Button> moveButtons_[4];
	
	std::unique_ptr<SFP::AnimationSprite> playerAvatar_;
	
	sf::Text dispAttributes_[12];
	sf::RectangleShape attribRects_[2];
	void MakeDispAttributes();
	
	
	std::unique_ptr<SFP::AnimationSprite> opponentAvatar_;

	void CreateArena();
	void CreateMoveButtons();
	void CreateWellnessBars();
	
	void MakePlayerAvatar();
	void MakeOpponentAvatar();
	
	void GenerateNewOpponent();
	
	sf::RectangleShape wellnessBars_[8];
	

public:
	explicit Arena(CMGT_PrototypeGame& game);
	void Begin(const sf::String& string, const Avatar& avatar, const Attributes& attributes, const Difficulty& difficulty);

	void EndTurn();
	void Render(sf::RenderWindow& window) override;
	
	void Save();
	
	void CreateExitButton();
	void UpdateAttribDisplay();
};
