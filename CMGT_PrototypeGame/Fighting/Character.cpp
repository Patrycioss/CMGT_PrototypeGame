#include "Character.hpp"

const Attributes& Character::attributes() const {
	return attributes_;
}

Character::Character(const Attributes& attributes) 
	: attributes_(attributes), wellness_({attributes.strength *3, attributes.wits * 2})
{

}

const Wellness& Character::wellness() const {
	return wellness_;
}

const unsigned int& Character::enemiesSlain() const {
	return enemiesSlain_;
}

const unsigned int& Character::damageDone() const {
	return damageDone_;
}

void Character::Attack(Character& opponent) {

}

void Character::Prepare() {

}

void Character::Recover() {

}

void Character::CastMagic(Character& opponent) 
{

}

Character::Character() {

}
