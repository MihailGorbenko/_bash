#pragma once
#include <Windows.h>
#include <string>
#include <iostream>
enum
{
	white = 0x007,
	red   = 0x0004,
	blue  = 0x0003,
	green = 0x0002,
	darkBlue = 0x00010

};

class Display
{
public:
	Display();
	~Display();
	void displayInfo(const std::string &);
	void displayErr(const std::string &);
	void displayDir(const std::string &);
	void displayFile(const std::string &);
	void displayStatus(const std::string &);
private:
	HANDLE		 stdCon;
};

