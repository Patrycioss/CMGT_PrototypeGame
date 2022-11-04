#include "ScoreViewer.hpp"

#include <memory>

ScoreViewer::ScoreViewer(const sf::Vector2f& position) 
	: SFP::AnimationSprite(position, "scoreViewer.png", 1, 1, 1)
{
	reloadButton_ = std::make_unique<Button>(position, "reload.png", 2, 2, 1);
	reloadButton_->Move(-reloadButton_->size().x,0);
	reloadButton_->animation().SetCycle(1, 1);

	reloadButton_->SetPointerEnterAction([&]() { 
		reloadButton_->animation().SetCycle(2, 1); 
	});

	reloadButton_->SetPointerExitAction([&]() { 
		reloadButton_->animation().SetCycle(1, 1); 
	});

	reloadButton_->SetClickAction([&]() {
		ScoreManager::LoadScores();
		Refresh();
	});
	
	AddChild(reloadButton_.get());


	eraseButton_ = std::make_unique<Button>(position, "sweepData.png", 15, 15, 1);
	eraseButton_->SetScale(1.5f,1.5f);
	eraseButton_->Move(-eraseButton_->size().x,size().y - eraseButton_->size().y);
	eraseButton_->animation().SetCycle(1, 1);
	eraseButton_->animation().SetDelay(100);

	eraseButton_->SetPointerEnterAction([&]() { 
		eraseButton_->animation().SetCycle(1, 15); 
	});

	eraseButton_->SetPointerExitAction([&]() { 
		eraseButton_->animation().SetCycle(1, 1); 
	});

	eraseButton_->SetClickAction([&]() {
		ScoreManager::DeleteScores();
		Refresh();
	});

	AddChild(eraseButton_.get());	
	
	
	ScoreManager::LoadScores();
	Refresh();
	ScoreManager::SaveScores();
}

void ScoreViewer::Refresh() 
{
	for (int i = 0; i < 8; i++)
	{
		if (scoreCards_[i] != nullptr) 
			RemoveChild(scoreCards_[i].get());
		
		if (i >= ScoreManager::sortedScores().size()) scoreCards_[i].reset();
		else {
			
			scoreCards_[i] = std::make_unique<ScoreCard>(sf::Vector2f{position().x, position().y + ((float) i * 47)},
			                                             *ScoreManager::sortedScores()[i]);
			AddChild(scoreCards_[i].get());
		}
	}
}

void ScoreViewer::Clear() 
{
	for (auto& scoreCard : scoreCards_)
	{
		scoreCard = nullptr;
	}
}