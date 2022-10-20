#pragma once
#include "GameObject.hpp"

namespace SFMLPE
{
  class Scene : public GameObject
  {
  private:
	  const char* name_;
  public:
	  explicit Scene(const char* name);
	  ~Scene();
	  
	  void Start() override;
	  
	  const char* name();
	  
  };
}


