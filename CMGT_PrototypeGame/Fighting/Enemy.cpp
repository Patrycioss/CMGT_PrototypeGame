#include "Enemy.hpp"

Enemy::Enemy(const Difficulty& difficulty) 
{
	attributes_ = Character::GetRandomAttributes();
}
