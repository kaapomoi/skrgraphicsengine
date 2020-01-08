#include "Errors.h"
#include <cstdlib>

void fatalError(std::string errorString) {
	std::cout << errorString << "\n";
	std::cout << "Enter any key to quit...";
	int tmp;
	std::cin >> tmp;
	SDL_Quit();
	exit(-1);
}