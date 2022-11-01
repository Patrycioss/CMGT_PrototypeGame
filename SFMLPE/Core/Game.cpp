#include "Game.hpp"
#include <string>
#include "EventSystem/EventManager.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <thread>
#include <filesystem>

namespace SFP
{
  std::unique_ptr<sf::RenderWindow> Game::window_;
  
  //Adds a scene to the Game's list of scenes.
  //If the game already has a scene with the same name
  //it removes that scene and puts the new one in.
  void Game::AddScene(const char* name, Scene* scene) {
	  scenesIndex_.emplace(std::pair(name,scene));
  }

  void Game::AddScene(Scene* scene) {
	  scenesIndex_.emplace(std::pair(scene->name(),scene));
  }

  //Removes specified scene from the list of scenes.
  //Returns whether it succeeded.
  void Game::RemoveScene(const char* name) {
	  scenesIndex_.erase(name);
  }
  
  void Game::RemoveScene(const Scene* scene) {
	  scenesIndex_.erase(scene->name());
  }
  
  void Game::RemoveScene(const std::unique_ptr<Scene>& scene) 
  {
	  scenesIndex_.erase(scene->name());
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
	  
	  std::filesystem::current_path(newPath);
	  
	  sizeU_ = sf::Vector2u(windowWidth, windowHeight);
	  sizeF_ = sf::Vector2f((float) windowWidth, (float) windowHeight);

	  window_ = std::make_unique<sf::RenderWindow>(sf::VideoMode(sizeU_.x,sizeU_.y), windowName);
	  window_->setFramerateLimit(60);
	  
	  Start();
	  
	  while (window_->isOpen())
	  {
		  sf::Event event; // NOLINT(cppcoreguidelines-pro-type-member-init)
		  
		  while (window_->pollEvent(event))
		  {
			  if (event.type == sf::Event::Closed){
				  
				  window_->close();
				  End();
				  return;
			  }
			  EventManager::TriggerEvent(event);
		  }

		  window_->clear(sf::Color::Black);
		  
		  Update();
		  
		  for (auto pair : scenesIndex_) {
			  if (pair.second->Visible()) pair.second->Render(*window_);
			  pair.second->Update();
		  }
		  window_->display();

		  prevTime = clock.getElapsedTime().asSeconds();
	  }
  }

  void Game::Stop() 
  {
	  window_->close();
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

  sf::Vector2f Game::MousePosition() {
	  return {(float) sf::Mouse::getPosition(*window_).x, (float) sf::Mouse::getPosition(*window_).y};
  }

  const sf::RenderWindow& Game::window() {
	  return *window_;
  }
}