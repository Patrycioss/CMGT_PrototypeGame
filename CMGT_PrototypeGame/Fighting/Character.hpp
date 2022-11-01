#pragma once
#include <string>

enum class Difficulty
{
	Normal = 0,
	Hard = 1
};

struct Attributes
{
	unsigned int strength;
	unsigned int agility; //Only one that can be 0
	unsigned int wits;
};

struct Wellness
{
	unsigned int health; //3*strength -- if 0 die
	unsigned int sanity; //2*wits -- if 0 die
};

class Character
{
private:
	Attributes attributes_;
	Wellness wellness_;
	unsigned int enemiesSlain_;
	unsigned int damageDone_;
	
public:
	std::string name;
	
	explicit Character(const Attributes& attributes);
	Character();
	[[nodiscard]] const Attributes& attributes() const;
	[[nodiscard]] const Wellness& wellness() const;
	[[nodiscard]] const unsigned int& enemiesSlain() const;
	[[nodiscard]] const unsigned int& damageDone() const;
	
	//Actions:
	void Attack(Character& opponent);
	void Prepare();
	void Recover();
	void CastMagic(Character& opponent);
};
