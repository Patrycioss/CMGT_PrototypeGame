#include "TweenManager.hpp"

unsigned int TweenManager::lastID_;
std::vector<Tween*> TweenManager::tweens_;
std::vector<std::vector<Tween*>::iterator> TweenManager::tweensToBeRemoved_;
std::vector<Tween*> TweenManager::tweensToAdd_;

Tween* TweenManager::AddTween(Tween* tween)
{
	tweensToAdd_.push_back(tween);
	tween->ID_ = lastID_++;
	return tween;
}

void TweenManager::RemoveTween(const Tween* tween) 
{
	tweensToBeRemoved_.push_back(std::find(tweens_.begin(), tweens_.end(), tween));
}

void TweenManager::Update()
{
	for (auto it =  tweens_.begin(); it != tweens_.end(); it++) {
		if (*it == nullptr) {
			tweensToBeRemoved_.push_back(it);
			break;
		}
		
		Tween& tween = **it;
		
		if (tween.finished_) tweensToBeRemoved_.push_back(it);
		else tween.Update();
	}
	
	for (auto it : tweensToBeRemoved_)
	{
		printf("Cleared! \n");
		delete *it;
		tweens_.erase(it);
	}
	tweensToBeRemoved_.clear();
	
	
	for (auto& tween : tweensToAdd_)
	{
		tweens_.push_back(tween);
	}
	tweensToAdd_.clear();
}

void TweenManager::ClearTweens() 
{
	for (auto it =  tweens_.begin(); it != tweens_.end(); it++) {
		tweensToBeRemoved_.push_back(it);
	}
	
	for (auto& tween : tweensToBeRemoved_)
	{
		delete *tween;
		tweens_.erase(tween);
		printf("Cleared \n");
	}
	tweensToBeRemoved_.clear();
}
