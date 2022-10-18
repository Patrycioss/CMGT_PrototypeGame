#pragma once
#include "Scene.hpp"
#include "EventSystem/EventHandler.hpp"

namespace SFMLPE
{
  class Game
  {
  private:
	  std::vector<Scene> scenes_;
	  std::map<const char*, Scene*> scenesIndex_;
	  sf::Vector2f sizeF_;
	  sf::Vector2u sizeU_;
	  
  protected:
	  virtual void Start();
	  virtual void Update();
	  
	  
	  EventHandler eventHandler;
	  
  public:
	  void Run(const int& windowWidth, const int& windowHeight, const char* windowName, const char* resourcePath);
	  
	  Scene& AddScene(const char* name);
	  bool RemoveScene(const char* name);
	  Scene& scene(const char* name);
	  
	  const sf::Vector2f& sizeF();
	  const sf::Vector2u& sizeU();
  };
}


