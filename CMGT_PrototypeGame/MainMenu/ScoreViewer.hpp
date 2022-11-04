#pragma once
#include "../../SFMLPE/SFMLPE.hpp"
#include "ScoreCard.hpp"
#include "../Button.hpp"

class ScoreViewer : public SFP::AnimationSprite
{
private:
	std::unique_ptr<ScoreCard> scoreCards_[8];
	std::unique_ptr<Button> reloadButton_;
	std::unique_ptr<Button> eraseButton_;
	
	void Clear();
	
public:
	explicit ScoreViewer(const sf::Vector2f& position);
	
	void Refresh();
};
