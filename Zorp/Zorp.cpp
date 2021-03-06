// Zorp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <windows.h>
#include <random>
#include <time.h>

const char* ESC = "\x1b";
const char* CSI = "\x1b[";
const char* TITLE = "\x1b[5;20H";
const char* INDENT = "\x1b[5C";
const char* YELLOW = "\x1b[93m";
const char* MAGENTA = "\x1b[95m";
const char* RESET_COLOR = "\x1b[0m";
const char* SAVE_CURSOR_POS = "\x1b[s";
const char* RESTORE_CURSOR_POS = "\x1b[u";

void main()
{ 
	const int EMPTY = 0;
	const int ENEMY = 1;
	const int TREASURE = 2;
	const int FOOD = 3;
	const int ENTRANCE = 4;
	const int EXIT = 5;
	const int MAX_RANDOM_TYPE = FOOD + 1;

	const int MAZE_WIDTH = 10;
	const int MAZE_HEIGHT = 6;

	DWORD dwMode = 0;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleMode(hOut, &dwMode);
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dwMode);
	
	int height = 0;
	char firstLetterOfName = 0;
	int avatarHP = 0;

	int rooms[MAZE_HEIGHT][MAZE_WIDTH];

	srand(time(nullptr));

	for (int y = 0; y < MAZE_HEIGHT; y++) {
		for (int x = 0; x < MAZE_WIDTH; x++) {
			rooms[y][x] = rand() % MAX_RANDOM_TYPE;
		}
	}
	rooms[0][0] = ENTRANCE;
	rooms[MAZE_HEIGHT - 1][MAZE_WIDTH - 1] = EXIT;

	std::cout << TITLE << MAGENTA << "Welcome to ZORP!" << RESET_COLOR << std::endl;
	std::cout << INDENT << "ZORP is a game of adventure, danger, and low cunning." << std::endl;
	std::cout << INDENT << "It is definitely not related to any other text-based adventure game." << std::endl;
	
	std::cout << "First, some questions..." << std::endl;
	
	std::cout << SAVE_CURSOR_POS;
	std::cout << INDENT << "How tall are you, in centimeters? " << INDENT << YELLOW;

	std::cin >> height;
	std::cout << RESET_COLOR << std::endl;

	if (std::cin.fail()) {
		std::cout << INDENT << "You have failed the first challenge are eaten by a Gru." << std::endl;
	}
	else {
		std::cout << INDENT << "You entered " << height << std::endl;
	}

	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cin.get();

	// move the cursor to the start of the 1st question
	std::cout << RESTORE_CURSOR_POS;
	// delete the next 4 lines of text
	std::cout << CSI << "4M";

	std::cout << INDENT << "What is the first letter of your name? " << INDENT << YELLOW;

	std::cin >> firstLetterOfName;
	std::cout << RESET_COLOR << std::endl;

	if (std::cin.fail() || !isalpha(firstLetterOfName)) {
		std::cout << INDENT << "You have failed the second challenge and you have been Default Danced on." << std::endl;
	}
	else {
		std::cout << INDENT << "You entered " << firstLetterOfName << std::endl;
	}
	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cin.get();

	std::cout << RESTORE_CURSOR_POS;
	std::cout << CSI << "A";
	std::cout << CSI << "4M";

	if (firstLetterOfName != 0) {
		avatarHP = (float)height / (firstLetterOfName * 0.02f);
	}
	else {
		avatarHP = 0;
	}

	std::cout << INDENT << "Using a complex deterministic algorithm, it has been calculated that you have " << avatarHP << " hit point(s)." << std::endl;

	std::cout << std::endl << INDENT << "Press 'Enter' to exit the program." << std::endl;
	std::cin.get(); 
	return;
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
