#include "TimerManager.hpp"

std::vector<Timer> TimerManager::timers_;
std::vector<Timer> TimerManager::timersToBeAdded_;
std::vector<std::vector<Timer>::iterator> TimerManager::timersToBeRemoved_;

void TimerManager::AddTimer(const Timer& timer) 
{
	timersToBeAdded_.push_back(timer);
}

void TimerManager::RemoveTimer(const Timer& timer)
{
	timersToBeRemoved_.push_back(std::find(timers_.begin(), timers_.end(),timer));
}

void TimerManager::Update() {
	
	for (auto& it : timersToBeRemoved_)
		timers_.erase(it);

	timersToBeRemoved_.clear();

	for (Timer& timer : timersToBeAdded_)
		timers_.push_back(timer);

	timersToBeAdded_.clear();

	for (Timer& timer : timers_)
		timer.Update();
}

void TimerManager::ClearTimers() {
	for (auto it =  timers_.begin(); it != timers_.end(); it++) {
		timersToBeRemoved_.push_back(it);
	}

	for (auto& timer : timersToBeRemoved_)
	{
		timers_.erase(timer);
		printf("Cleared \n");
	}
	timersToBeRemoved_.clear();
}
