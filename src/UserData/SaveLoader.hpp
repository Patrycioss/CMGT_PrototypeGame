#pragma once
#include "../Character/Character.hpp"

struct SaveInformation
{
	Character player;
	Character opponent;
	Difficulty difficulty;
	unsigned int damageDone{};
	unsigned int enemiesSlain{};
	bool playerTurn{};
};

class SaveLoader
{
private:
	
public:
	static bool retainOldSaves;
	
	static void Save(const Character& player, const Character& opponent, const Difficulty& difficulty, const unsigned int& enemiesSlain, const bool& playerTurn);
	static void CopyLatestToNew();
	static SaveInformation Load(const std::string& path);
};
