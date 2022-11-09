#include "Timer.hpp"
#include "TimerManager.hpp"

#include <utility>

unsigned int Timer::lastID_ = 0;

Timer::Timer(const sf::Time& duration, std::function<void()>  onEndAction) 
	: duration_(duration), onEndAction_(std::move(onEndAction))
	{
		ID_ = lastID_++;
	}

void Timer::Update() {
	if (clock_.getElapsedTime().asMilliseconds() >= duration_.asMilliseconds()) 
		Finish();
}

void Timer::Finish()
{
	onEndAction_();
	TimerManager::RemoveTimer(*this);
	
}

bool Timer::operator==(const Timer& timer) const {
	return (ID_ == timer.ID_);
};