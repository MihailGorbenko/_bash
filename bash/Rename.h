#pragma once
#include "Command.h"
#include "Copy.h"
#include"Remove.h"

#include<string>

class Rename :
	public Command
{
public:
	Rename(std::string,std::string,std::string);
	~Rename();
	void exec();
private:
	std::string src,
				dst,
				curPath;
	Display outDev;
};

