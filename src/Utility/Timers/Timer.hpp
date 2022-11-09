#pragma once


#include "../../Engine/GameObject.hpp"

class Timer
{
private:
	sf::Clock clock_;
	std::function<void()> onEndAction_;
	sf::Time duration_;
	
	static unsigned int lastID_;
	unsigned int ID_;
	
public:
	void Update();

	Timer(const sf::Time& duration, std::function<void()>  onEndAction);

	bool operator==(const Timer& timer) const;

	void Finish();
};
