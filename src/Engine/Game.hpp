#pragma once
#include "Scene.hpp"
#include "EventSystem/EventHandler.hpp"


class Game
{
private:
	std::map<const char*, Scene*> scenesIndex_;
	static sf::Vector2f sizeF_;
	static sf::Vector2u sizeU_;

	sf::Clock clock;
	float prevTime;

	static std::unique_ptr<sf::RenderWindow> window_;

protected:
	virtual void Start();
	virtual void Update();
	virtual void End();


	EventHandler eventHandler;

public:
	void Run(const int& windowWidth, const int& windowHeight, const char* windowName, const std::string& resourcePath);
	static void Stop();

	void AddScene(const char* name, Scene* scene);
	void AddScene(Scene* scene);
	void RemoveScene(const Scene* scene);
	void RemoveScene(const char* name);
	void RemoveScene(const std::unique_ptr<Scene>& scene);

	Scene* scene(const char* name);

	static sf::Vector2f& sizeF();
	static sf::Vector2u& sizeU();

	static Game* instance;

	static const sf::RenderWindow& window();

	float deltaTime();
	sf::Time elapsedTime();

	static sf::Vector2f MousePosition();
};