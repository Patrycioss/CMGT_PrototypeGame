#pragma once
#include "SFMLPE/SFMLPE.hpp"

class TestGame : public SFMLPE::Game
{
private:
	float speed = 2;
protected:
	void Start() override;
	void Update() override;
};