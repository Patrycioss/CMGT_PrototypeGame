#include "Character.hpp"

#include <utility>
#include "effolkronium/random.hpp"

std::array<std::string, 12> Character::possibleNames_
{
		"Blood Elf", "Lich King", "Demon Hunter", "Arthas", "Illidan", "Kaelthas",
		"Patrick", "Yvens", "Jelle", "Bas", "Wiebe", "Koen"
};

const Attributes& Character::attributes() const {
	return attributes_;
}

Character::Character()
	: attributes_(), wellness_{1000,1000,1000}, avatar_{Avatar::None}
{};

void Character::Init(std::string name, const Avatar& avatar, const Attributes& attributes) 
{
	attributes_ = attributes;
	if (!attributes_.IsFull()) attributes_.FillRemainingPoints();
	wellness_.GenerateFromAttributes(attributes_);
	
	name_ = std::move(name);
	if (name_.empty()) name_ = GetRandomName();
	
	if (avatar == Avatar::None) avatar_ = GetRandomAvatar();
	else avatar_ = avatar;
}

const Wellness& Character::wellness() const {
	return wellness_;
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

void Character::Damage(const unsigned int& amount)
{
	wellness_.health -= amount;
	
	if (wellness_.health > wellness_.maxHealth || wellness_.health <= 0)
	{
		wellness_.health = 0;
		Kill();	
	}
}

void Character::Heal(const unsigned int& amount)
{
	wellness_.health += amount;
	
	if (wellness_.health > wellness_.maxHealth) 
		wellness_.health = wellness_.maxHealth;
}

void Character::Kill()
{
	
}

Attributes Character::GetRandomAttributes() {
	return GetRandomAttributes(Attributes());
}


Attributes Character::GetRandomAttributes(const Attributes& attributes)
{
	Attributes newAttributes(attributes);

	unsigned int pointsLeft = 8 - newAttributes.strength - newAttributes.agility - newAttributes.wits;

	if (pointsLeft == 0)
	{
		newAttributes = Attributes();
		pointsLeft = 6;
	}

	while (pointsLeft != 0)
	{
		pointsLeft--;

		switch (effolkronium::random_static::get(0,2))
		{
			case 0:
				newAttributes.agility++;
				break;

			case 1:
				newAttributes.wits++;
				break;

			case 2:
				newAttributes.strength++;
				break;
		}
	}

	return newAttributes;
}

const Avatar& Character::avatar() const {
	return avatar_;
}

std::string Character::GetRandomName() {
	return *effolkronium::random_static::get(possibleNames_);	
}

Avatar Character::GetRandomAvatar() {
	return Avatar(effolkronium::random_static::get(1,3));
}

