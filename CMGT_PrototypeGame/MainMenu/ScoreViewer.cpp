#include "ScoreViewer.hpp"

ScoreViewer::ScoreViewer(const sf::Vector2f& position) 
	: SFMLPE::AnimationSprite(position, "scoreViewer.png", 1, 1, 1)
{
	Clear();
	Refresh();
	ScoreManager::SaveScores();
	printf("Amount: %s \n", scoreCards_[1]->score().name.c_str());
}

void ScoreViewer::Refresh() 
{
	ScoreManager::LoadScores();
	ScoreManager::SortScores();
	
	
	for (int i = 0; i < 8; i++)
	{
		if (i >= ScoreManager::sortedScores().size() && scoreCards_[i] != nullptr)
		{
			RemoveChild(scoreCards_[i].get());
			scoreCards_[i] = nullptr;
			continue;
		}
		
		if (scoreCards_[i] == nullptr && i < ScoreManager::sortedScores().size())
		{
			scoreCards_[i] = std::make_unique<ScoreCard>(sf::Vector2f{position().x, position().y + ((float)i * 47)}
			, *ScoreManager::sortedScores()[i]);

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