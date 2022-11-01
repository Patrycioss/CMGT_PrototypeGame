#pragma once
#include "../../SFMLPE/SFMLPE.hpp"
#include "ScoreCard.hpp"
#include "../Deprecated/ReloadButton.hpp"
#include "../Deprecated/EraseButton.hpp"
#include "../NewButton.hpp"

class ScoreViewer : public SFP::AnimationSprite
{
private:
	std::unique_ptr<ScoreCard> scoreCards_[8];
	std::unique_ptr<NewButton> reloadButton_;
	std::unique_ptr<NewButton> eraseButton_;
	
	void Clear();
	
public:
	explicit ScoreViewer(const sf::Vector2f& position);
	
	void Refresh();
};
