#pragma once
#include "Command.h"
#include "BashExeptions.h"

#include <io.h>
#include <direct.h>
#include <string>
#include <iostream>


class MakeDir :
	public Command
{
public:
	MakeDir(std::string &,std::string &);
	~MakeDir();
	void exec() throw(BashErrInfo);
private:
	std::string dstPath,
				currPath;
};

