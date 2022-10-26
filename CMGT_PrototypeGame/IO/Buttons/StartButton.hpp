#pragma once
#include "Button.hpp"

class StartButton : public Button
{
public:
	explicit StartButton(const sf::Vector2f& position);
	
	void OnPointerEnter() override;
	void OnPointerExit() override;
};


