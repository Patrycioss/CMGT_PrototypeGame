#include "ReloadButton.hpp"

ReloadButton::ReloadButton(const sf::Vector2f& position)
		: Button(position, "reload.png", 2, 2, 1)
{
	animation().SetCycle(1, 1, 0);
}

void ReloadButton::OnPointerEnter() {
	animation().SetCycle(2, 1, 0);
}

void ReloadButton::OnPointerExit() {
	animation().SetCycle(1, 1, 0);
}

