#pragma once
#include "SFML/Graphics.hpp"
#include "EventHandler.hpp"
#include "../Game.hpp"

class EventManager
{
	friend Game;

private:
	static unsigned int lastHandlerID_;
	static std::map<unsigned int, EventHandler*> handlers;

	static void TriggerEvent(const sf::Event&);

public:
	static unsigned int GetLastHandlerID();
	static unsigned int AddHandler(EventHandler* eventHandler);
	static void RemoveHandler(const unsigned int& ID);
};