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
  Scene& Game::AddScene(const char* name) {
	  scenes_.emplace_back(Scene(name));
	  scenesIndex_[name] = &scenes_.back();
	  return *scenesIndex_.at(name);
  }

  //Removes specified scene from the list of scenes.
  //Returns whether it succeeded.
  bool Game::RemoveScene(const char* name) {
	  delete scenesIndex_[name];
	  return scenesIndex_.erase(name) != 0;
  }

  Scene& Game::scene(const char* name) {
	  return *scenesIndex_.at(name);
  }
  
  //This function is called at the start of the game.
  //Use it to initialize your GameObjects in your Game instance.
  void Game::Start(){}
  

  void Game::Run(const int& windowWidth, const int& windowHeight, const char* windowName, const char* resourcePath) 
  {
	  std::string newPath = resourcePath;
	  std::filesystem::current_path("../" + newPath);
	  
	  sizeU_ = sf::Vector2u(windowHeight, windowWidth);
	  sizeF_ = sf::Vector2f((float) windowWidth, (float) windowHeight);

	  sf::RenderWindow window(sf::VideoMode(sizeU_), windowName);
	  window.setFramerateLimit(60);
	  
	  Start();
	  
	  while (window.isOpen())
	  {
		  sf::Event event; // NOLINT(cppcoreguidelines-pro-type-member-init)
		  
		  while (window.pollEvent(event))
		  {
			  if (event.type == sf::Event::Closed)
				  window.close();

			  EventManager::TriggerEvent(event);
		  }

		  window.clear(sf::Color::Black);
		  
		  Update();

		  for (auto pair : scenesIndex_) {
			  if (pair.second->Visible()) pair.second->Render(window);
		  }
		  window.display();
	  }
  }

  const sf::Vector2f& Game::sizeF() {
	  return sizeF_;
  }

  const sf::Vector2u& Game::sizeU() {
	  return sizeU_;
  }

  void Game::Update() {

  }
}