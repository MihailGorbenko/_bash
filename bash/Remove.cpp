#include "Remove.h"



Remove::Remove(const std::string &rPh,std::string &currPh)
	: rPath(rPh),
	  currPath(currPh)
{
}


Remove::~Remove()
{
}

void Remove::exec()  throw(BashErrInfo)
{
	FILE *test;
	if (rPath.find(':') != std::string::npos)       //if absolute path
	{
		currPath = rPath;
	}
	else if (rPath.find('/') == std::string::npos)   //if relative path
	{
		currPath += rPath;
	}

	if (_access(currPath.c_str(), 00) != 0)         //if exist
	{
		throw BashErrInfo("Such file or directory doesn't exist!");
	}
	if ((test = fopen(currPath.c_str(), "r")) == NULL)  // if dir
	{
		recRem(currPath);
	}
	else                                     //if file
	{
		fclose(test);
		outDev.displayStatus("Removing... >" + currPath);
		remove(currPath.c_str());
		outDev.displayStatus("Done!");

	}
}

void Remove::recRem(std::string & path)
{
	std::string action = "Removing... >";
	std::string tempPath = path,
		        mask     = "*.*";
	tempPath += '/';
	_finddata_t found;
	int resList;
	int status;
	resList = _findfirst((tempPath + mask).c_str(), &found);
	status = resList;
	while (status != -1)
	{
		if (strcmp(found.name, ".") != 0
			&& strcmp(found.name, "..") != 0)
		{
			if (found.attrib&_A_SUBDIR)
			{
				recRem(tempPath + found.name);
			}
			else
			{
				std::string temp = tempPath + found.name;
				
				outDev.displayStatus(action + temp);
				remove(temp.c_str());
			}
		}
		status = _findnext(resList, &found);
	}
	_findclose(resList);
	outDev.displayStatus(action + path);
	_rmdir(path.c_str());
	outDev.displayStatus("Done!");
}
