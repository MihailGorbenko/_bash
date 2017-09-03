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

	_finddata_t  *foundFile = new _finddata_t;
	long resultList;
    int status;

	resultList = _findfirst(currPath.c_str(), foundFile);
	status = resultList;
	if (status != -1)    //if file
	{
		if (foundFile->attrib&_A_SUBDIR)
		{
			recRem(currPath);
		}
		else
		{
			remove(currPath.c_str());
		}
	}
	delete foundFile;
	_findclose(resultList);
}

void Remove::recRem(std::string & path)
{
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
				recRem(tempPath += found.name);
			}
			else
			{
				remove((tempPath + found.name).c_str());
			}
		}
		status = _findnext(resList, &found);
	}
	_findclose(resList);
	_rmdir(path.c_str());
}
