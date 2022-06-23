#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <windows.h>
#include <locale>
#include <climits>
#include "gamecore.h"

class Game : public GameCore
{
private:
	std::string word;
	std::string predictedWord;
	std::vector<char> guessedLetters;

	bool Guess(char letter);
public:
	Game(std::string word);
	~Game();

	bool Play(GameMode mode);
};