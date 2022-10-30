#pragma once
#include <vector>
#include <map>
#include <memory>


struct Score
{
	std::string name;
	int damageDone;
	int enemiesSlain;
};

class ScoreManager
{
private:
	static std::map<std::string, Score> scoresMap_;
	static std::vector<Score*> sortedScores_;

public:
	static void LoadScores();
	static void StoreScore(const std::string& name, const Score& data);
	static void RemoveScore(const std::string& name);
	static void SortScores();

	static void SaveScores();
	
	static const Score& score(const std::string& name);
	static const std::vector<Score*>& sortedScores();
	static void DeleteScores();
};

