#pragma once
#include "Command.h"
#include "BashExeptions.h"
#include "Display.h"

#include <string>
#include <io.h>
#include <direct.h>
#include <string.h>

class Remove :
	public Command
{
public:
	Remove(const std::string &,std::string & );
	~Remove();
	void exec() throw(BashErrInfo);
private:
	void recRem(std::string &path);
	std::string rPath,
				currPath;
	Display outDev;
};

