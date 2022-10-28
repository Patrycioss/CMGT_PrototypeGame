#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include <functional>

namespace SFMLPE
{
	class EventHandler
	{
	private:
		unsigned int ID_;
		std::map<sf::Event::EventType, std::function<void(const sf::Event&)>> subscriptions;

	public:
		EventHandler();
		void CallSubscription(const sf::Event& eventType);
		void Subscribe(const sf::Event::EventType& eventType, const std::function<void(const sf::Event&)>& method);
		void Unsubscribe(const sf::Event::EventType& eventType);

		~EventHandler();
	};
}


