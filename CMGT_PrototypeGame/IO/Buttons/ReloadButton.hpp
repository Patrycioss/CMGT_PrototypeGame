#pragma once

#include "Button.hpp"

class ReloadButton : public Button
{
public:
	ReloadButton(const sf::Vector2f& position);
	void OnPointerExit() override;
	void OnPointerEnter() override;
};