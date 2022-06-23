#include "game.h"

Game::Game(std::string word) 
{
	this->word = word;
	this->predictedWord = "";
	for (int i = 0; i < word.length(); i++)
	{
		this->predictedWord += "*";
	}
}

Game::~Game() 
{

}

bool Game::Guess(char letter) 
{
	bool found = false;
	this->guessedLetters.push_back(letter);
	for (int i = 0; i < this->word.length(); i++) 
	{
		if (static_cast<int>(letter) == static_cast<int> (this->word[i]))
		{
			found = true;
			this->predictedWord[i] = letter;
		}
	}
	return found;
}

bool Game::Play(GameMode mode)
{
	std::string HANGMAN[7] =
	{
"                ------   \n\
		|    |   \n\
		|        \n\
		|        \n\
		|        \n\
		|        \n\
		|        \n\
		|        \n\
		|        \n\
		-------- ",

"                ------   \n\
		|    |   \n\
		|    O  |\n\
		|        \n\
		|        \n\
		|        \n\
		|        \n\
		|        \n\
		|        \n\
		-------- ",

"                ------   \n\
		|    |   \n\
		|    O   \n\
		| -+-    \n\
		|        \n\
		|        \n\
		|        \n\
		|        \n\
		|        \n\
		-------- ",

"                ------   \n\
		|    |   \n\
		|    O   \n\
		|  /-+-/ \n\
		|        \n\
		|        \n\
		|        \n\
		|        \n\
		|        \n\
		-------- ",

"                ------   \n\
		|    |   \n\
		|    O   \n\
		|  /-+-/ \n\
		|    |   \n\
		|        \n\
		|        \n\
		|        \n\
		|        \n\
		-------- ",

"                ------   \n\
		|    |   \n\
		|    O   \n\
		|  /-+-/ \n\
		|    |   \n\
		|    |   \n\
		|   |    \n\
		|   |    \n\
		|        \n\
		-------- ",

"                ------   \n\
		|    |   \n\
		|    O   \n\
		|  /-+-/ \n\
		|    |   \n\
		|    |   \n\
		|   | |  \n\
		|   | |  \n\
		|        \n\
		-------- "
	};
	int tries = 0;
	if (mode == GameMode::ExtraHard) 
	{
		tries = 5;
	}
	bool letterExist = false;
	bool win = false;

	while (tries < 6) 
	{
		if (!letterExist) 
		{
			system("CLS");
			std::cout << HANGMAN[tries] << std::endl << std::endl;
		}
		else 
		{
			std::cout << "Вы уже вводили эту букву!" << std::endl;
			letterExist = false;
		}
		std::cout << predictedWord << std::endl;
		if (mode == GameMode::Casual) std::cout << "Чтобы сдаться введите 1" << std::endl;
		std::cout << "Введите букву: ";
		char letter;
		std::cin >> letter;
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		if (mode == GameMode::Casual && static_cast<int>(letter) == static_cast<int>('1')) tries = 6;
		letter = std::tolower(letter, std::locale(".1251"));
		if (std::find(std::begin(guessedLetters), std::end(guessedLetters), letter) != std::end(guessedLetters)) 
		{
			letterExist = true;
			continue;
		}
		bool correct;
		correct = this->Guess(letter);

		if (!correct && mode != GameMode::Casual) tries += 1;

		if (!this->word.compare(this->predictedWord)) 
		{
			system("CLS");
			std::cout << HANGMAN[tries] << std::endl << std::endl;
			std::cout << predictedWord << std::endl;
			std::cout << std::endl << "Победа!" << std::endl;
			system("PAUSE");
			return true;
		}
	}


	system("CLS");
	std::cout << HANGMAN[tries] << std::endl << std::endl;
	std::cout << "Вы проиграли! Загаданное слово: " << this->word << std::endl;
	system("PAUSE");
	return false;
}