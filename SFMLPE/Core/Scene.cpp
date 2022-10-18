#include "Scene.hpp"
#include "SFML/System/Clock.hpp"

namespace SFMLPE
{
  SFMLPE::Scene::Scene(const char* name) : GameObject(1,0,true){
	  name_ = name;
  };

  const char *Scene::name() {
	  return name_;
  }

  Scene::Scene(const Scene& scene) : GameObject(scene.position()){
	  name_ = scene.name_;
  }
}

