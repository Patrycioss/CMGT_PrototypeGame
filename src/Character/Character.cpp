#include "Character.hpp"

#include <cmath>
#include <utility>
#include "effolkronium/random.hpp"


std::array<std::string, 13> Character::possibleNames_
{
		"Blood Elf", "Lich King", "Demon Hunter", "Arthas", "Illidan", "Kaelthas",
		"Patrick", "Yvens", "Jelle", "Bas", "Wiebe", "Koen", "Paul"
};

const Attributes& Character::attributes() const {
	return attributes_;
}

Character::Character()
	: attributes_(), wellness_{1000,1000,1000}, avatar_{Avatar::None}, prepared_(false), outputLog_(nullptr), damageDone_(0){};

void Character::Init(std::string name, const Avatar& avatar, const Attributes& attributes) 
{
	attributes_ = attributes;
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
	
	int damage;
	
	if (prepared_)
	{
		prepared_ = false;
		damage = (int) attributes_.strength + effolkronium::random_static::get(2, (int)attributes_.agility*2) 
				- (int) (std::ceil(attributes_.strength/2));
	}
	else damage = (int)((attributes_.strength + effolkronium::random_static::get(1,4)) - (std::ceil(opponent.attributes().strength/2)));
	
	if (damage == 0)
	{
		if (outputLog_ != nullptr) outputLog_->Push(name_ + " failed to attack " + opponent.name() + " , he kinda sucks");
		return;
	}

	if (opponent.Damage(damage))
	{
		damageDone_ += damage;
		if (outputLog_ != nullptr) outputLog_->Push(name_ + " attacked " + opponent.name() + " for " + std::to_string(damage) + " damage");
	}
	else if (outputLog_ != nullptr) outputLog_->Push(name_ + " tried to attack " + opponent.name() + " but they dodged their attack!");
}

void Character::Prepare() {
	prepared_ = true;

	if (outputLog_ != nullptr) outputLog_->Push(name_ + " is cooking something up...");
}

void Character::Recover() {
	
	int healthRecovered = 0;
	int sanityRecovered = 0;
	
	
	if (effolkronium::random_static ::get(1,100) <= std::ceil(attributes_.wits * 1.5) * 11)
	{
		healthRecovered = effolkronium::random_static::get(0,3);
		sanityRecovered = effolkronium::random_static::get(1,2);

		wellness_.health += healthRecovered;

		if (wellness_.health > wellness_.maxHealth)
			wellness_.health = wellness_.maxHealth;
		
		wellness_.sanity += sanityRecovered;
		
		if (wellness_.sanity > wellness_.maxSanity)
			wellness_.sanity = wellness_.maxSanity;

		if (outputLog_ != nullptr) outputLog_->Push(name_ + " recovered " + std::to_string(healthRecovered) + " health and " + std::to_string(sanityRecovered) + " sanity");
	}
	else if (outputLog_ != nullptr) outputLog_->Push(name_ + " failed to recover any health or sanity...");
}

void Character::CastMagic(Character& opponent) 
{
	int damage = (int)attributes_.wits + effolkronium::random_static::get(-3,3);
	
	if (damage == 0)
	{
		if (outputLog_ != nullptr) outputLog_->Push(name_ + " cast a spell but missed...");
	} 

	else if (damage < 0) {
		opponent.Break(damage);
		
		if (outputLog_ != nullptr) outputLog_->Push(name_ + " cast a spell and broke " + opponent.name() + "'s sanity for " + std::to_string(-damage) + " points");
	}
	else
	{
		damageDone_ += damage;
		opponent.Damage(damage);
		if (outputLog_ != nullptr) outputLog_->Push(name_ + " cast a spell and dealt " + std::to_string(damage) + " damage to " + opponent.name());
	}
	
}

bool Character::Damage(const unsigned int& amount)
{
	if (prepared_)
	{
		prepared_ = false;
		int chance = (int) attributes_.agility * 10;
		if (effolkronium::random_static::get(1,100) < chance) return false;
	}
	
	wellness_.health -= amount;
	
	if (wellness_.health > wellness_.maxHealth || wellness_.health <= 0)
	{
		wellness_.health = 0;
	}
	return true;
}

void Character::Break(const unsigned int& amount)
{
	wellness_.sanity -= amount;

	if (wellness_.sanity > wellness_.maxSanity || wellness_.sanity <= 0)
	{
		wellness_.sanity = 0;
		Kill();
	}}

void Character::Kill()
{
	if (outputLog_ != nullptr) outputLog_->Push(name_ + " has fallen!");

	if (onDeathAction_) onDeathAction_();
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

const std::string& Character::name() const {
	return name_;
}

void Character::Tremble() {
	if (outputLog_ != nullptr) outputLog_->Push(name_ + " trembles in fear!");
}

void Character::SetOutputLog(OutputLog& outputLog) {
	outputLog_ = &outputLog;
}

void Character::SetOnDeathAction(const std::function<void()>& action) {
	onDeathAction_ = action;
}

const unsigned int& Character::damageDone() const {
	return damageDone_;
}

void Character::KillPrep() {
	prepared_ = false;
}

void Character::OverrideDamageDone(const unsigned int& damage) {
	damageDone_ = damage;
}