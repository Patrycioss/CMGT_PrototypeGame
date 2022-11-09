#include "OutputLog.hpp"
#include "../Engine/ResourceManager.hpp"

void OutputLog::Push(const std::string& string) 
{
	for (int i = 0; i < 3; i ++)
	{
		outputs_[i].setString(outputs_[i + 1].getString());
	}
	
	outputs_[3].setString(string);
}

void OutputLog::Render(sf::RenderWindow& window) {
	for (sf::Text& text : outputs_) window.draw(text);
	GameObject::Render(window);
}

OutputLog::OutputLog(const sf::Vector2f& position) 
	: GameObject(position)
{
	for (int i = 0 ; i < 4; i ++)
	{
		outputs_[i].setFillColor(sf::Color::Black);
		outputs_[i].setFont(*ResourceManager::LoadFont("fonts/minecraftFont.ttf"));
		outputs_[i].setCharacterSize(30);
		outputs_[i].setPosition(position.x + 10, position.y + (float)(40 * i) + 10);
	}
}
