#include "Find.h"



Find::Find(std::string &name, std::string &currPh) :
	findName(name),
	currPath(currPh)
{
};


Find::~Find()
{
}

void Find::exec()  
{
	if (findName.find(':') == std::string::npos)  //if relative path
	{
		findName = currPath + '/' + findName;
	}

	_finddata_t found;
	long resList;
	int  status;

	resList = _findfirst(findName.c_str(), &found);
	status = resList;

	while (status != -1)
	{
		if (strcmp(found.name, ".") != 0 && strcmp(found.name, "..") != 0)
		{
			if (found.attrib & _A_SUBDIR)
			{
				outpDev.displayDir(found.name);
			}
			else
			{
				outpDev.displayFile(found.name);
			}
		}
		status = _findnext(resList, &found);
	}
	_findclose(resList);
}


