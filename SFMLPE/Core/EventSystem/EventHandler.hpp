#pragma once
#include <map>
#include <SFML/Graphics.hpp>

namespace SFMLPE
{
	class EventHandler
	{
	private:
		unsigned int ID_;
		std::map<sf::Event::EventType, std::function<void(sf::Event)>> subscriptions;

	public:
		EventHandler();
		void CallSubscription(const sf::Event& eventType);
		void Subscribe(const sf::Event::EventType& eventType, const std::function<void(sf::Event)>& method);
		void Unsubscribe(const sf::Event::EventType& eventType);

		~EventHandler();
	};
}


