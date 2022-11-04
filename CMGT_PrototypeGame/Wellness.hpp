#pragma once
#include "Attributes.hpp"

struct Wellness
{
	unsigned int maxHealth;
	unsigned int health; //3*strength -- if 0 die
	unsigned int sanity; //2*wits -- if 0 die
	
	void GenerateFromAttributes(const Attributes& attributes)
	{
		health = 3 * attributes.strength;
		maxHealth = health;
		
		sanity = 2 * attributes.wits;
	}
};
