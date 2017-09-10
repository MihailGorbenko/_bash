#pragma once
#include "Command.h"
#include "Display.h"

#include <string>
#include <io.h>
#include <direct.h>

class Find :
	public Command
{
public:
	Find(std::string &name,std::string &currPh);
	~Find();
	void exec();

private:
	std::string findName,
		        currPath;
	Display outpDev;
};

