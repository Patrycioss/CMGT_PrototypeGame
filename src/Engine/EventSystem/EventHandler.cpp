#include "EventHandler.hpp"
#include "EventManager.hpp"


std::map<sf::Event::EventType, const std::function<void(sf::Event)>> subscriptions;


EventHandler::EventHandler()
{
	ID_ = EventManager::AddHandler(this);
}

void EventHandler::CallSubscription(const sf::Event& event)
{
	if (subscriptions.contains(event.type))
		subscriptions[event.type](event);
}

void EventHandler::Subscribe(const sf::Event::EventType& eventType, const std::function<void(const sf::Event&)>& method)
{
	subscriptions[eventType] = method;
}

void EventHandler::Unsubscribe(const sf::Event::EventType &eventType)
{
	if (subscriptions.contains(eventType)) subscriptions.erase(eventType);
}

EventHandler::~EventHandler()
{
	EventManager::RemoveHandler(ID_);
}