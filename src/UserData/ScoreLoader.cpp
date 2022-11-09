#include <fstream>
#include <iostream>
#include <algorithm>
#include "ScoreLoader.hpp"

std::map<std::string, Score> ScoreLoader::scoresMap_;
std::vector<Score*> ScoreLoader::sortedScores_;


void ScoreLoader::StoreScore(const std::string& name, const Score& data) {
	bool alreadyHasIt = scoresMap_.contains(name);
	
	scoresMap_[name] = data;
	
	if (!alreadyHasIt) sortedScores_.push_back(&scoresMap_[name]);
}

void ScoreLoader::RemoveScore(const std::string& name) {
	sortedScores_.erase(std::find(sortedScores_.begin(), sortedScores_.end(), &scoresMap_[name]));
	scoresMap_.erase(name);
}

void ScoreLoader::SaveScores()
{
	std::ofstream dataWrite("../user_data/scores.cmgt");
	
	if (!dataWrite.fail())
	{
		dataWrite.clear();
		
		for (std::pair<std::string, Score> pair : scoresMap_)
		{
			std::string entry;
			
			entry += pair.second.name;
			entry += '|';
			entry += std::to_string(pair.second.damageDone);
			entry += '|';
			entry += std::to_string(pair.second.enemiesSlain);
			entry += "|\n";
			
			dataWrite.write(entry.c_str(), (long) entry.size());
		}
		dataWrite.close();
	}
}

void ScoreLoader::LoadScores() {
	scoresMap_.clear();
	sortedScores_.clear();
	
	std::ifstream dataRead("../user_data/scores.cmgt");
	
	if (!dataRead.fail())
	{
		while (!dataRead.eof())
		{
			std::string line;

			std::getline(dataRead, line);
		
			if (line.empty()) continue;
			if (line.find('|') == std::string::npos) continue;
	
			Score newData;

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
	
	SortScores();
}


void ScoreLoader::SortScores() 
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
}

void ScoreLoader::DeleteScores()
{
	scoresMap_.clear();
	sortedScores_.clear();
	SaveScores();
}

const Score& ScoreLoader::score(const std::string& name) 
{
	return scoresMap_[name];
}

const std::vector<Score*>& ScoreLoader::sortedScores() {
	return sortedScores_;
}
