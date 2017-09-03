#include "MakeDir.h"


MakeDir::MakeDir(std::string &destPh, std::string &currPh) :
	dstPath(destPh),
	currPath(currPh)
{
}


MakeDir::~MakeDir()
{
}

void MakeDir::exec() throw(BashErrInfo)
{

	if (dstPath.find('/') == std::string::npos)   //if relative path
	{
		currPath += dstPath;

	}

	else if (dstPath.find(':') != std::string::npos)  //if full path
	{
		currPath = dstPath;
	}

	if (_access(currPath.c_str(), 00) == 0)
	{
		throw BashErrInfo("Such directory alredy exist!");
	}

	if (currPath.back() != '/') currPath += '/';

	if (_mkdir(currPath.c_str()) == -1)
	{
		throw BashErrInfo("Can't create directory!");
	}
}
