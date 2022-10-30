#include "../MainMenu/ScoreViewer.hpp"


EraseButton::EraseButton(const sf::Vector2f& position) 
	: Button(position, "sweepData.png", 15, 15, 1)
{
	animation().SetCycle(1,1);
	animation().SetDelay(150);
}

void EraseButton::OnPointerExit() {
	animation().SetCycle(1,1);
}

void EraseButton::OnPointerEnter() {
	animation().SetCycle(1,15);	
}

void EraseButton::OnClick() {
	ScoreViewer* scoreViewer = dynamic_cast<ScoreViewer*>(parent());
	ScoreManager::DeleteScores();
	scoreViewer->Refresh();
}
