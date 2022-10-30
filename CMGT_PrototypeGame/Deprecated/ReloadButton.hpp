#pragma once

#include "Button.hpp"

class ReloadButton : public Button
{
private:
//	ScoreViewer& scoreViewer_;
	
public:
//	ReloadButton(const sf::Vector2f& position, ScoreViewer& scoreViewer);
	ReloadButton(const sf::Vector2f& position);
	void OnPointerExit() override;
	void OnPointerEnter() override;
	void OnClick() override;
};