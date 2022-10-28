#include <fstream>
#include <iostream>
#include <algorithm>
#include "ScoreManager.hpp"

std::map<std::string, Score> ScoreManager::scoresMap_;
std::vector<Score*> ScoreManager::sortedScores_;


void ScoreManager::StoreScore(const std::string& name, const Score& data) {
	bool alreadyHasIt = scoresMap_.contains(name);
	
	scoresMap_[name] = data;
	
	if (!alreadyHasIt) sortedScores_.push_back(&scoresMap_[name]);
}

void ScoreManager::RemoveScore(const std::string& name) {
	sortedScores_.erase(std::find(sortedScores_.begin(), sortedScores_.end(), &scoresMap_[name]));
	scoresMap_.erase(name);
}

void ScoreManager::SaveScores()
{
	std::ofstream dataRead("../scores.cmgt");
	
	if (!dataRead.fail())
	{
		dataRead.clear();
		
		for (std::pair<std::string, Score> pair : scoresMap_)
		{
			std::string entry;
			
			entry += pair.second.name;
			entry += '|';
			entry += std::to_string(pair.second.damageDone);
			entry += '|';
			entry += std::to_string(pair.second.enemiesSlain);
			entry += "|\n";
			
			dataRead.write(entry.c_str(), (long) entry.size());
		}
	}
}

void ScoreManager::LoadScores() {
	std::ifstream dataRead("../scores.cmgt");
	
	if (!dataRead.fail())
	{
		while (!dataRead.eof())
		{
			std::string line;

			std::getline(dataRead, line);
		
			if (line.empty()) continue;
			if (line.find('|') == std::string::npos) continue;
	
			Score newData{};

			bool nameDone = false;
			bool damageDoneDone = false;

			std::string chars;

			for (char const &c : line) {
				if (c == '|') {
					if (!nameDone) {
						char nameBuffer[chars.size()];
						chars.copy(nameBuffer, chars.size());
						
						nameBuffer[chars.size()] = '\0';
						newData.name = nameBuffer;
						
						
						nameDone = true;
					} else if (!damageDoneDone) {
						newData.damageDone = std::stoi(chars);
						damageDoneDone = true;
					} else newData.enemiesSlain = std::stoi(chars);

					chars.clear();
				} else chars.push_back(c);
			}
			
			bool alreadyHadIt = scoresMap_.contains(newData.name);
			
			scoresMap_[newData.name] = newData;
			
			if (!alreadyHadIt) 
				sortedScores_.push_back(&scoresMap_[newData.name]); 
		}
		
		dataRead.close();
	}
}


void ScoreManager::SortScores() 
{
	for (int i = (int) sortedScores_.size()-1; i >= 0; i-- )
	{
		for (int j = i - 1; j >= 0; j--)
		{
			if (sortedScores_[i]->enemiesSlain > sortedScores_[j]->enemiesSlain)
			{
				auto a = sortedScores_[i];
				sortedScores_[i] = sortedScores_[j];
				sortedScores_[j] = a;
			}
		}
	}
	
//	for (auto& test : sortedScores_)
//	{
//		printf("Name: %s, val: %d \n", test->name.c_str(), test->enemiesSlain);
//	}
}

const Score& ScoreManager::score(const std::string& name) 
{
	return scoresMap_[name];
}

const std::vector<Score*>& ScoreManager::sortedScores() {
	return sortedScores_;
}
