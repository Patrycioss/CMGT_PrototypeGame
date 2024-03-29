﻿#include "TweenManager.hpp"

unsigned int TweenManager::lastID_;
std::vector<std::unique_ptr<Tween>> TweenManager::tweens_;
std::vector<std::vector<std::unique_ptr<Tween>>::iterator> TweenManager::tweensToBeRemoved_;
std::vector<Tween*> TweenManager::tweensToAdd_;

Tween* TweenManager::AddTween(Tween* tween)
{
	tweens_.push_back(std::unique_ptr<Tween>(tween));
	tween->ID_ = lastID_++;
	return tween;
}

void TweenManager::Update()
{
	for (auto& tween : tweens_)
	{
		if (tween->finished_) tweensToBeRemoved_.push_back(std::find(tweens_.begin(), tweens_.end(), tween));
		else tween->Update();
	}

	for (auto it : tweensToBeRemoved_)
	{
		tweens_.erase(it);
	}
	tweensToBeRemoved_.clear();
}

void TweenManager::ClearTweens() 
{

	for (auto it =  tweens_.begin(); it != tweens_.end(); it++) {			
		tweensToBeRemoved_.push_back(it);
	}

	for (auto& tween : tweensToBeRemoved_)
	{
		tweens_.erase(tween);
		printf("Cleared \n");
	}
	tweensToBeRemoved_.clear();
}