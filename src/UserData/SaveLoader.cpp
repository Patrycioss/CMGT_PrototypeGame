#include "SaveLoader.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>


bool SaveLoader::retainOldSaves = false;

void SaveLoader::CopyLatestToNew()
{
	int index;

	std::ifstream indexRead("../user_data/index.cmgt");

	if (indexRead.fail()) {
		std::ofstream indexWrite("../user_data/index.cmgt");
		indexWrite << "0";
		index = 0;
		indexWrite.close();
	}
	else 
	{
		{
			std::string line;
			while (indexRead >> line);

			try {
				index = std::stoi(line);
			}
			catch (const std::exception& e) {
				throw std::runtime_error("Index.cmgt doesn't contain a valid index!");
				indexRead.close();
				return;
			}
		}
		indexRead.close();

		std::ofstream indexOpen("../user_data/index.cmgt");
		indexOpen.clear();

		int newIndex = index + 1;
		std::string string = std::to_string(newIndex);

		indexOpen.write(string.c_str(), (long) string.size());
		indexOpen.close();
	}
	
	std::string string = "../user_data/save" + std::to_string(index) + ".cmgt";
	std::filesystem::copy_file("../user_data/latest_save.cmgt",string);
}

void SaveLoader::Save(const Character& player, const Character& opponent, const Difficulty& difficulty, const unsigned int& enemiesSlain, const bool& playerTurn) 
{
	if (!std::filesystem::exists("../user_data/"))
	{
		std::filesystem::create_directory("../user_data");
	}
	else if (std::filesystem::exists("../user_data/latest_save.cmgt") && retainOldSaves)
		CopyLatestToNew();
	
	std::ofstream fileWrite("../user_data/latest_save.cmgt");
	fileWrite.clear();
	
	fileWrite << player.name() << std::endl;
	
	fileWrite << std::to_underlying(player.avatar()) << std::endl;
	
	fileWrite << player.attributes().agility << std::endl;
	fileWrite << player.attributes().wits << std::endl;
	fileWrite << player.attributes().strength << std::endl;
	
	fileWrite << player.wellness().maxHealth << std::endl;
	fileWrite << player.wellness().health << std::endl;
	fileWrite << player.wellness().maxSanity << std::endl;
	fileWrite << player.wellness().sanity << std::endl;
	
	fileWrite << opponent.name() << std::endl;

	fileWrite << std::to_underlying(opponent.avatar()) << std::endl;

	fileWrite << opponent.attributes().agility << std::endl;
	fileWrite << opponent.attributes().wits << std::endl;
	fileWrite << opponent.attributes().strength << std::endl;

	fileWrite << opponent.wellness().maxHealth << std::endl;
	fileWrite << opponent.wellness().health << std::endl;
	fileWrite << opponent.wellness().maxSanity << std::endl;
	fileWrite << opponent.wellness().sanity << std::endl;
	
	fileWrite << std::to_underlying(difficulty) << std::endl;
	fileWrite << player.damageDone() << std::endl;
	fileWrite << enemiesSlain << std::endl;
	fileWrite << playerTurn;
	
	fileWrite.close();
}

SaveInformation SaveLoader::Load(const std::string& path)
{
	std::ifstream fileRead("../user_data/latest_save.cmgt");
	
	std::function<int()> readLineToInt = [&fileRead]() -> int
	{
		std::string line;
		std::getline(fileRead,line);
		
		int n;
		
		try {
			n = std::stoi(line);
		}
		catch (std::exception& e)
		{
			printf("Failed to convert %s to a number! \n", line.c_str());
		}
		return n;
	};

	SaveInformation saveInformation;
	{
		std::string name;
		std::getline(fileRead, name);
		
		Avatar avatar = Avatar(readLineToInt());
		int agility = readLineToInt();
		int wits = readLineToInt();
		int strength = readLineToInt();
		
		int maxHealth = readLineToInt();
		int health = readLineToInt();
		int maxSanity = readLineToInt();
		int sanity = readLineToInt();
		
		saveInformation.player.Init(name, avatar, Attributes{(unsigned int) agility,(unsigned int) wits,(unsigned int) strength});
		saveInformation.player.wellness_ = Wellness{(unsigned int) maxHealth, (unsigned int) health, (unsigned int) maxSanity, (unsigned int) sanity};
	}
	
	{
		std::string name;
		std::getline(fileRead, name);

		Avatar avatar = Avatar(readLineToInt());
		int agility = readLineToInt();
		int wits = readLineToInt();
		int strength = readLineToInt();

		int maxHealth = readLineToInt();
		int health = readLineToInt();
		int maxSanity = readLineToInt();
		int sanity = readLineToInt();

		saveInformation.opponent.Init(name, avatar, Attributes{(unsigned int) agility,(unsigned int) wits,(unsigned int) strength});
		saveInformation.opponent.wellness_ = Wellness{(unsigned int) maxHealth, (unsigned int) health, (unsigned int) maxSanity, (unsigned int) sanity};
	}
	
	saveInformation.difficulty = Difficulty(readLineToInt());
	saveInformation.damageDone = readLineToInt();
	saveInformation.enemiesSlain = readLineToInt();
	saveInformation.playerTurn = readLineToInt();
	
	fileRead.close();
	
	return saveInformation;
}
