#include "Scene.hpp"
#include "SFML/System/Clock.hpp"
#include "Game.hpp"

namespace SFP {
  SFP::Scene::Scene(const char* name)
		  : GameObject(0,0, true) 
		  , name_(name)
		  {};
  
  Scene::~Scene()
  {
	  Game::instance->RemoveScene(name_);
  }
  
  const char* Scene::name() const {
	  return name_;
  }
}

