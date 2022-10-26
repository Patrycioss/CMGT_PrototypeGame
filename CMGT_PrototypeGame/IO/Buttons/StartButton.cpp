#include "StartButton.hpp"

StartButton::StartButton(const sf::Vector2f& position) 
	: Button(position, "startButton.png", 6, 1, 6)
{
	GetAnimation()->SetCycle(0,3,400);
}

void StartButton::OnPointerEnter(){
	GetAnimation()->SetCycle(3,3,400);
}

void StartButton::OnPointerExit() {
	GetAnimation()->SetCycle(0,3,400);
}


