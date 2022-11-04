#pragma once
#include "SFML/Graphics.hpp"


class Tween
{
	friend class TweenManager;
	
private:
	bool finished_ = false;
	
protected:
	sf::Clock coolDownTimer_;
	std::function<void()> onEnd_;
	
	unsigned int ID_;
	sf::Time totalDuration_;
	
	void Finish();
	void Abort();
	
public:
	virtual void Update();
	
	void SetEndAction(const std::function<void()>& action);
	
	Tween* operator+= (std::function<void()>& onEnd);
	bool operator==(const Tween& tween) const;
};