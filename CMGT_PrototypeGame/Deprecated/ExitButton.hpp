#pragma once
#include "Button.hpp"

class ExitButton : public Button
{
public:
	explicit ExitButton(const sf::Vector2f& position);

	void OnPointerEnter() override;
	void OnPointerExit() override;
};