#pragma once
#include "GameObject.hpp"

namespace SFP
{
  class Scene : public GameObject
  {
  private:
	  const char* name_;
	  
  public:
	  explicit Scene(const char* name);
	  ~Scene();
	  
	  [[nodiscard]] const char* name() const;
	  
  };
}


