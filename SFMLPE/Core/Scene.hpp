#pragma once
#include "GameObject.hpp"

namespace SFMLPE
{
  class Scene : GameObject
  {
  private:
	  const char* name_;
	  
  public:
	  explicit Scene(const char* name);
	  const char* name();
  };
}


