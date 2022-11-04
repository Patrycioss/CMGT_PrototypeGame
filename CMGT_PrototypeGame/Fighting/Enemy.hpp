#pragma once
#include "Character.hpp"

class Enemy : public Character
{
public:
	explicit Enemy(const Difficulty& difficulty);
};
