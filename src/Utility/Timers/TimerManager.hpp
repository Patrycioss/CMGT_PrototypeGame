#pragma once
#include "Timer.hpp"

class TimerManager
{
private:
	static std::vector<Timer> timers_;
	static std::vector<Timer> timersToBeAdded_;
	static std::vector<std::vector<Timer>::iterator> timersToBeRemoved_;
	
public:
	static void AddTimer(const Timer& timer);
	
	static void Update();
	static void RemoveTimer(const Timer& timer);
	
	static void ClearTimers();
};
