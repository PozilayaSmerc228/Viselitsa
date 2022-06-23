#include <iostream>
#include <windows.h>
#include <vector>
#include <fstream>
#include <random>
#include <locale>
#include "gamecore.h"
#include "game.h"
#include "statistics.h"

bool MainMenu();
void StartGame(int mode);
void AddNewWord();
void LoadWords(std::vector<std::string>& words);

int main()
{
    system("color 0A");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    while (MainMenu());
    return 0;
}

bool MainMenu()
{
    system("CLS");
    std::string NAME = "\
#####   ##  ##   ####   ######     ###  ##  ##  ##  ##   ####\n\
##  ##  ##  ##  ##  ##  ##        # ##  ##  ##  ##  ##  ##  ##\n\
#####   ## ###  ##      ####     #  ##  ## ###  ##  ##  ######\n\
##  ##  ### ##  ##  ##  ##      ##  ##  ### ##  ##  ##  ##  ##\n\
#####   ##  ##   ####   ######  ##  ##  ##  ##   ### ## ##  ## ";
    std::cout << NAME << std::endl << std::endl;
    std::cout << "1) Новая игра" << std::endl;
    std::cout << "2) Добавить слово" << std::endl;
    std::cout << "3) Статистика" << std::endl;
    std::cout << "4) Выйти из игры" << std::endl;

    int answer;
    std::cin >> answer;

    switch (answer)
    {
    case 1:
    {
        while (true)
        {
            system("CLS");
            std::cout << "Сложность:" << std::endl;
            std::cout << "1) Казуальная" << std::endl;
            std::cout << "2) Обычная" << std::endl;
            std::cout << "3) Кошмар" << std::endl;
            std::cout << "Выберите сложность: ";

            int submenu;
            std::cin >> submenu;
            submenu -= 1;

            if (submenu == 0 || submenu == 1 || submenu == 2)
            {
                StartGame(submenu);
                break;
            }
        }
        break;
    }
    case 2:
    {
        AddNewWord();
        break;
    }
    case 3:
    {
        system("CLS");
        Statistics* stats = new Statistics();
        stats->parseFile("./stats.txt");
        int loses, wins;
        std::cout << "Статистика:" << std::endl << std::endl;
        std::cout << "---------------------------------------" << std::endl;
        std::cout << "Казуальная" << std::endl;
        std::cout << "Побед/поражений" << std::endl;
        std::tie(loses, wins) = stats->getStats(GameCore::GameMode::Casual);
        std::cout << wins << "/" << loses << std::endl;
        std::cout << "---------------------------------------" << std::endl;
        std::cout << "Обычная" << std::endl;
        std::cout << "Побед/поражений" << std::endl;
        std::tie(loses, wins) = stats->getStats(GameCore::GameMode::Regular);
        std::cout << wins << "/" << loses << std::endl;
        std::cout << "---------------------------------------" << std::endl;
        std::cout << "Кошмар" << std::endl;
        std::cout << "Побед/поражений" << std::endl;
        std::tie(loses, wins) = stats->getStats(GameCore::GameMode::ExtraHard);
        std::cout << wins << "/" << loses << std::endl;
        std::cout << "---------------------------------------" << std::endl;
        delete stats;
        system("PAUSE");
        break;
    }
    case 4:
    {
        return false;
    }
    default:
    {
        return true;
    }
    }
}

void StartGame(int mode)
{
    std::vector <std::string> words;
    LoadWords(words);

    std::random_device r;
    std::default_random_engine seed(r());
    std::uniform_int_distribution<int> rnd(0, words.size() - 1);



    Game* game = new Game(words[rnd(seed)]);
    Statistics* stats = new Statistics();
    stats->parseFile("./stats.txt");

    stats->updateStats(static_cast<GameCore::GameMode>(mode), game->Play(static_cast<Game::GameMode>(mode)));

    stats->saveToFile("./stats.txt");

    delete stats;
    delete game;
}

void AddNewWord()
{
    system("CLS");
    std::string temp;
    std::vector<std::string> words;
    LoadWords(words);
    std::cout << "Введите новое слово: ";
    std::cin >> temp;
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    std::for_each(temp.begin(), temp.end(), [](char& c) { c = std::tolower(c, std::locale(".1251")); });
    if (std::find(std::begin(words), std::end(words), temp) == std::end(words))
    {
        std::ofstream out;
        out.open("./words.txt", std::ios::app);
        out << std::endl << temp;
        out.close();
        std::cout << "Слово добавлено в словарь!" << std::endl;
        system("PAUSE");
    }
    else
    {
        std::cout << "Такое слово уже есть!" << std::endl;
        system("PAUSE");
    }
}

void LoadWords(std::vector<std::string>& words)
{
    std::string temp;
    std::ifstream file("./words.txt");

    while (std::getline(file, temp))
    {
        words.push_back(temp);
    }
    file.close();
}