#pragma once
#include "../../SFMLPE/SFMLPE.hpp"
#include "ScoreCard.hpp"
#include "../IO/Buttons/ReloadButton.hpp"

class ScoreViewer : public SFMLPE::AnimationSprite
{
private:
	std::unique_ptr<ScoreCard> scoreCards_[8];
	std::unique_ptr<ReloadButton> reloadButton_;
	
	void Clear();
	
public:
	explicit ScoreViewer(const sf::Vector2f& position);
	
	void Refresh();

};
