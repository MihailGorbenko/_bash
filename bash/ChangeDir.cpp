#include "ChangeDir.h"

ChangeDir::ChangeDir(string nPath,string &currPath) : currPh(currPath),newPh(nPath)
{
}

ChangeDir::~ChangeDir(){}

void ChangeDir::exec() throw (BashErrInfo)
{

	if (newPh.compare("../") == 0)                  // if return to previous
	{
		if (currPh.length() > 3)
		{
			int slash = currPh.rfind('/', currPh.size() - 2);
			currPh = currPh.substr(0, slash + 1);
		}
	}
	 
	else if (newPh.find(':') != string::npos)       //if  full path
	{
		if (newPh.back() != '/') newPh += '/';
		if (_access(newPh.c_str(), 00) == 0)
		{
			currPh = newPh;
		}
		else throw BashErrInfo("Invalid path!");
	}

	else if (newPh.find('/') == string::npos)       //if relative path
	{
		string tempPh = currPh + newPh + '/';
		if (_access(tempPh.c_str(), 00) == 0)
		{
			currPh = tempPh;
		}
		else throw BashErrInfo("Such directory doesn't exist!");
	}

	
}
