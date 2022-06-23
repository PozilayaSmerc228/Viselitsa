#pragma once
#include <tuple>
#include <string>
#include <fstream>
#include "gamecore.h"

class Statistics : public GameCore
{
private:
	int** statistics;

public:
	Statistics();
	~Statistics();

	std::tuple<int, int> getStats(GameMode mode);
	void updateStats(GameMode mode, bool win);
	void parseFile(std::string path);
	void saveToFile(std::string path);
};

