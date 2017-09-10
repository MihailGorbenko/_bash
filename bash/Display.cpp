#include "Display.h"



Display::Display() :
	stdCon(GetStdHandle(STD_OUTPUT_HANDLE))
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}


Display::~Display()
{
}

void Display::displayInfo(const std::string &msg)
{
	int pathPos = msg.find_first_of(':') + 1;
	std::cout << msg.substr(0, pathPos);
	SetConsoleTextAttribute(
		stdCon,
		red | 
		FOREGROUND_INTENSITY);

	std::cout << msg.substr(pathPos, (msg.size() - pathPos - 1));

	SetConsoleTextAttribute(
		  stdCon,
		  white  );

		std::cout<< msg.at(msg.length() - 1);
}

void Display::displayErr(const std::string &msg)
{
	SetConsoleTextAttribute(
		stdCon,
		green |
		FOREGROUND_INTENSITY);
	std::cout << msg << std::endl;
	SetConsoleTextAttribute(
		stdCon,
		white );
}

void Display::displayDir(const std::string &msg)
{
	SetConsoleTextAttribute(
		stdCon,
		blue |
		FOREGROUND_INTENSITY);
	std::cout << msg << std::endl;
	SetConsoleTextAttribute(
		stdCon,
		white);
}

void Display::displayFile(const std::string &msg)
{
	std::cout << msg <<std::endl;
}

void Display::displayStatus(const std::string &msg)
{

	SetConsoleTextAttribute(
		stdCon,
		darkBlue |
		FOREGROUND_INTENSITY);
	std::cout << msg << std::endl;
	SetConsoleTextAttribute(
		stdCon,
		white);
}
