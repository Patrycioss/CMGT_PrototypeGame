#pragma once


#include "../Engine/GameObject.hpp"

class OutputLog : public GameObject
{
private:
	sf::Text outputs_[4];
	
public:
	OutputLog(const sf::Vector2f& position);
	
	void Push(const std::string& string);
	
	void Render(sf::RenderWindow& window) override;
};
