#include "EventManager.hpp"

namespace SFMLPE
{
	unsigned int EventManager::lastHandlerID_;
	std::map<unsigned int, EventHandler*> EventManager::handlers;

	unsigned int EventManager::AddHandler(EventHandler* eventHandler)
	{
		lastHandlerID_++;
		handlers.emplace(lastHandlerID_, eventHandler);
		return lastHandlerID_;
	}

	void EventManager::TriggerEvent(const sf::Event& event)
	{
		for (auto pair: handlers)
			pair.second->CallSubscription(event);
	}

	void EventManager::RemoveHandler(const unsigned int& ID)
	{
		handlers.erase(ID);
	}

	unsigned int EventManager::GetLastHandlerID()
	{
		return lastHandlerID_;
	}
}
