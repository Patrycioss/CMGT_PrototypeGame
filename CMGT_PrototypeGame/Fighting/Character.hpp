#pragma once
#include <string>
#include <array>
#include "../Attributes.hpp"
#include "../Wellness.hpp"

enum class Avatar
{
	None,
	Illidan,
	Arthas,
	Kaelthas
};

enum class Difficulty
{
	Normal,
	Hard
};

class Character
{
protected:
	Avatar avatar_;
	Attributes attributes_;
	Wellness wellness_;
	
	std::string name_;

	static std::array<std::string, 12> possibleNames_;
	
public:
	Character();
	void Init(std::string name, const Avatar& avatar, const Attributes& attributes);
	
	[[nodiscard]] const Attributes& attributes() const;
	[[nodiscard]] const Wellness& wellness() const;
	[[nodiscard]] const Avatar& avatar() const;
	
	//Actions:
	void Attack(Character& opponent);
	void Prepare();
	void Recover();
	void CastMagic(Character& opponent);
	
	void Kill();
	void Damage(const unsigned int& amount);
	void Heal(const unsigned int& amount);
	static Attributes GetRandomAttributes(const Attributes& attributes);
	static Attributes GetRandomAttributes();
	
	[[nodiscard]] static std::string GetRandomName();
	[[nodiscard]] static Avatar GetRandomAvatar();
};
