#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>


#include "Command.h"
#include "Copy.h"
#include "Find.h"
#include "MakeDir.h"
#include "Move.h"
#include "Remove.h"
#include "ShowDir.h"
#include "ChangeDir.h"
#include "CreateFile.h"
#include "BashExeptions.h"

enum exCmnd {      //command names
	mv,
	rm,
	cp,
	grep,
	cd,
	ls,
	makedir,
	touch,
	ex_it,
	clearCon,
	no_command
};

class Bash
{
public:
	Bash();
	~Bash();
	void getCommand() throw(BashErrInfo);
	void execute();
	void setCurrPath(std::string cP);
	std::string getCurrPath();

private:
	void check();
	Command    *currCommand;               //current command pointer
	std::string      curPath;              //current path
	vector<std::string> utils;            //vector for utils names comparing
};

