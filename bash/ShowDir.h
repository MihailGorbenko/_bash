#pragma once
#include "Command.h"
#include "Display.h"

#include <io.h>
#include <string>
#include <iostream>
#include <list>
#include <cstring>


class ShowDir :
	public Command
{
public:
	ShowDir(const std::string path);
	~ShowDir();
	void exec();
private:
	std::string path;
	Display outp;
};

