#include "statistics.h"

Statistics::Statistics() 
{
	this->statistics = new int* [3];
	for (int i = 0; i < 3; i++) this->statistics[i] = new int[2] {0, 0};
}

Statistics::~Statistics()
{
	for (int i = 0; i < 3; i++) delete[] this->statistics[i];
	delete[] this->statistics;
}

std::tuple<int, int> Statistics::getStats(GameMode mode) 
{
	return std::make_tuple(this->statistics[static_cast<int>(mode)][0], this->statistics[static_cast<int>(mode)][1]);
}

void Statistics::updateStats(GameMode mode, bool win) 
{
	this->statistics[static_cast<int>(mode)][static_cast<int>(win)] += 1;
}

void Statistics::parseFile(std::string path) 
{
	std::string temp;
	std::ifstream file(path);

	for (int i = 0; i < 3; i++) 
	{
		for (int j = 0; j < 2; j++) 
		{
			std::getline(file, temp, ' ');
			this->statistics[i][j] = std::stoi(temp);
		}
	}
}

void Statistics::saveToFile(std::string path) 
{
	std::ofstream out;
	out.open(path);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			out << this->statistics[i][j] << " ";
		}
	}
	out.close();
}