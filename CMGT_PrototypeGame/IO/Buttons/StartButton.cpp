#include "StartButton.hpp"

StartButton::StartButton(const sf::Vector2f& position) 
	: Button(position, "startButton.png", 6, 6, 1)
{
	animation().SetCycle(1,3,400);
}

void StartButton::OnPointerEnter(){
	animation().SetCycle(4, 3);
}

void StartButton::OnPointerExit() {
	animation().SetCycle(1, 3);
}

void StartButton::Update() {
	Button::Update();
}
