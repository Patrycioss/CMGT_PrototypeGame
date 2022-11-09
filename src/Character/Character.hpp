#pragma once
#include <string>
#include <array>
#include "Attributes.hpp"
#include "Wellness.hpp"
#include "../Arena/OutputLog.hpp"

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
	friend class SaveLoader;
	
private:
	OutputLog* outputLog_;
	
	bool prepared_;
	
	std::function<void()> onDeathAction_;
	
	unsigned int damageDone_;
	
protected:
	Avatar avatar_;
	Attributes attributes_;
	Wellness wellness_;
	
	std::string name_;

	static std::array<std::string, 13> possibleNames_;
	
public:
	Character();
	void Init(std::string name, const Avatar& avatar, const Attributes& attributes);
	
	[[nodiscard]] const Attributes& attributes() const;
	[[nodiscard]] const Wellness& wellness() const;
	[[nodiscard]] const Avatar& avatar() const;
	[[nodiscard]] const std::string& name() const;
	[[nodiscard]] const unsigned int& damageDone() const;
	
	//Actions:
	void Attack(Character& opponent);
	void Prepare();
	void KillPrep();
	void Recover();
	void CastMagic(Character& opponent);
	void Tremble();
	
	void SetOutputLog(OutputLog& outputLog);
	void SetOnDeathAction(const std::function<void()>& action);
	
	void Kill();
	bool Damage(const unsigned int& amount);
	static Attributes GetRandomAttributes(const Attributes& attributes);
	static Attributes GetRandomAttributes();
	
	[[nodiscard]] static std::string GetRandomName();
	[[nodiscard]] static Avatar GetRandomAvatar();
	void Break(const unsigned int& amount);

	void OverrideDamageDone(const unsigned int& damage);
};
