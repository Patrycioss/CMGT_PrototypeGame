#include "Game.hpp"
#include <string>
#include "EventSystem/EventManager.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <thread>

namespace SFMLPE
{
  //Adds a scene to the Game's list of scenes.
  //If the game already has a scene with the same name
  //it removes that scene and puts the new one in.
  void Game::AddScene(const char* name, Scene* scene) {
	  scenesIndex_.emplace(std::pair(name,scene));
  }

  //Removes specified scene from the list of scenes.
  //Returns whether it succeeded.
  void Game::RemoveScene(const char* name) {
	  scenesIndex_.erase(name);
  }

  Scene* Game::scene(const char* name) {
	  return scenesIndex_.at(name);
  }
  
  //This function is called at the start of the game.
  //Use it to initialize your GameObjects in your Game instance.
  void Game::Start(){}

  //This function is called every frame.
  void Game::Update(){}
  
  //This function is called after the user closes the window.
  //Use it to delete initialized objects.
  void Game::End(){}
  

  Game* Game::instance;
  
  sf::Vector2f Game::sizeF_;
  sf::Vector2u Game::sizeU_;
  
  void Game::Run(const int& windowWidth, const int& windowHeight, const char* windowName, const char* resourcePath) 
  {
	  instance = this;
	  
	  
	  std::string newPath = resourcePath;
	  
	  if (std::filesystem::current_path().has_relative_path())
	  
	  
	  std::filesystem::current_path("../" + newPath);
	  
	  sizeU_ = sf::Vector2u(windowWidth, windowHeight);
	  sizeF_ = sf::Vector2f((float) windowWidth, (float) windowHeight);

	  sf::RenderWindow window(sf::VideoMode(sizeU_), windowName);
	  window.setFramerateLimit(60);
	  
	  
	  Start();
	  for (auto pair : scenesIndex_)
	  {
		  pair.second->Start();
	  }
	  
	  while (window.isOpen())
	  {
		  sf::Event event; // NOLINT(cppcoreguidelines-pro-type-member-init)
		  
		  while (window.pollEvent(event))
		  {
			  if (event.type == sf::Event::Closed){
				  
				  window.close();
				  End();
				  return;

			  }
			  EventManager::TriggerEvent(event);
		  }

		  window.clear(sf::Color::Black);
		  
		  Update();

		  
		  for (auto pair : scenesIndex_) {
			  pair.second->mousePosition = {(float) sf::Mouse::getPosition(window).x, (float) sf::Mouse::getPosition(window).y};
			  if (pair.second->Visible()) pair.second->Render(window);
			  pair.second->Update();
		  }
		  window.display();

		  prevTime = clock.getElapsedTime().asSeconds();
	  }
  }

  sf::Vector2f& Game::sizeF() {
	  return sizeF_;
  }

  sf::Vector2u& Game::sizeU() {
	  return sizeU_;
  }

  float Game::deltaTime() {
	  return clock.getElapsedTime().asSeconds() - prevTime;
  }

  sf::Time Game::elapsedTime() {
	  return clock.getElapsedTime();
  }
}