#include "Scene.hpp"
#include "SFML/System/Clock.hpp"
#include "Game.hpp"

namespace SFMLPE {
  SFMLPE::Scene::Scene(const char* name)
		  : GameObject(0,0, true) {
	  name_ = name;
	  SetSize(Game::sizeF());
  };
  
  Scene::~Scene()
  {
	  Game::instance->RemoveScene(name_);
  }
  
  const char* Scene::name() {
	  return name_;
  }

  void Scene::Start() {
	  Game::instance->AddScene(name_, this);
	  GameObject::Start();
  }

}

