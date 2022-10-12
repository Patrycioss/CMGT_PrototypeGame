#include "Scene.hpp"

namespace SFMLPE
{
  SFMLPE::Scene::Scene(const char* name) : GameObject(0,0,false){
	  name_ = name;
  };

  const char *Scene::name() {
	  return name_;
  }
}

