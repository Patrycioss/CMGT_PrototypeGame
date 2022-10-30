#include "ReloadButton.hpp"
#include "../ScoreManager.hpp"
#include "../MainMenu/ScoreViewer.hpp"

//ReloadButton::ReloadButton(const sf::Vector2f& position, ScoreViewer& scoreViewer)
//		: Button(position, "reload.png", 2, 2, 1), scoreViewer_(scoreViewer)
//{
//	animation().SetCycle(1, 1, 0);
//}

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

void ReloadButton::OnClick() {
	ScoreViewer* scoreViewer = dynamic_cast<ScoreViewer*>(parent());
	ScoreManager::LoadScores();
	scoreViewer->Refresh();
}




