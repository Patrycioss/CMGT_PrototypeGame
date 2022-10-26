#include "ExitButton.hpp"

ExitButton::ExitButton(const sf::Vector2f& position)
		: Button(position, "startButton.png", 6, 1, 6)
{
	GetAnimation()->SetCycle(0,3,400);
}

void ExitButton::OnPointerEnter(){
	GetAnimation()->SetCycle(3,3,400);
}

void ExitButton::OnPointerExit() {
	GetAnimation()->SetCycle(0,3,400);
}
