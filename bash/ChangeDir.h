#pragma once

#include <string>
#include <io.h>
#include <direct.h>
#include <iostream>

#include "Command.h"
#include "BashExeptions.h"

using namespace std;

class ChangeDir :
	public Command
{
public:
	ChangeDir(string nPath, string &currPath) throw (BashErrInfo);
	~ChangeDir();
	void exec();
private:
    string & currPh;
	string newPh;
};

