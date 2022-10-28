#include "ExitButton.hpp"

ExitButton::ExitButton(const sf::Vector2f& position)
		: Button(position, "startButton.png", 6, 6, 1)
{
	this->animation().SetCycle(1, 3, 400);
}

void ExitButton::OnPointerEnter()
{
	this->animation().SetCycle(4, 3, 400);
}

void ExitButton::OnPointerExit() 
{
	this->animation().SetCycle(1, 3, 400);
}
