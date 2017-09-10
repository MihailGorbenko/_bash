#pragma once
#include <string>
#include <io.h>
#include <direct.h>
#include <string.h>

#include "Command.h"
#include "BashExeptions.h"
#include "Display.h"

enum dirStat
{
	existFile,
	CannotOpen_w,
	CannotOpen_r,
	CannotClose
};

class Copy :
	public Command
{
public:
	Copy(const std::string &,const std::string &, const std::string &);
	~Copy();
	void exec() throw (BashErrInfo);
private:
	void recCopy(std::string src, std::string dst);
	void copyFile(std::string src, std::string dst,bool nothrow,bool withFname) throw(dirStat);
	Display outDev;
	std::string srcPath,
				dstPath,
				currPath;
};

