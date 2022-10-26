#pragma once
#include "../../SFMLPE/SFMLPE.hpp"
#include "ScoreCard.hpp"

class ScoreViewer : public SFMLPE::AnimationSprite
{
private:
	std::unique_ptr<ScoreCard> scoreCards_[8];
	
	void Clear();
	
public:
	explicit ScoreViewer(const sf::Vector2f& position);
	
	void Refresh();

};
