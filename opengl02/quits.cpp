#include "quits.h"

void quitProgram() {
	std::exit(0);
}

void quitProgram(int code) {
	std::exit(code);
}

void Error(std::string msg) {
	std::cout << msg << std::endl;
	quitProgram(1);
}

void Warning(std::string msg) {
	std::cout << "Warning: " << msg << std::endl;
}

void Usage() {}