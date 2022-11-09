#pragma once
#include "ScoreCard.hpp"
#include "../Engine/Button.hpp"
#include "../Engine/AnimationSprite.hpp"

class ScoreViewer : public AnimationSprite
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
