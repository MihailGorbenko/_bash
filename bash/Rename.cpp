#include "Rename.h"



Rename::Rename(std::string source, std::string dest, std::string currP)
	: src(source),
	  dst(dest),
	  curPath(currP)
{
}


Rename::~Rename()
{
}

void Rename::exec()
{
	FILE *test;
	_finddata_t found;
	long resList;
	int status;
	if (src.find('/') == std::string::npos)   //if relative path
	{
		src = curPath + src;
	}
	if (_access(src.c_str(), 00) == -1) throw BashErrInfo("Wrong source path!"); // if not exist


	outDev.displayStatus("Renaming... >" + src);
	if ((test = fopen(src.c_str(), "r")) == NULL) //if dir
	{
		std::string newDir = curPath + dst;
		_mkdir(newDir.c_str());
		resList = _findfirst((src + "/*.*").c_str(), &found);
		status = resList;

		while (status != -1)
		{
			if (strcmp(found.name, ".") != 0 && strcmp(found.name, "..") != 0)
			{
				Copy cp((src + '/' + found.name), newDir, curPath);
				cp.exec();
			}
			status = _findnext(resList, &found);
		}
		_findclose(resList);
		Remove rm(src, curPath);
		rm.exec();
	}
	else                                //if file
	{
		fclose(test);
		dst = src.substr(0, src.rfind('/') + 1) + dst;
		rename(src.c_str(), dst.c_str());
	}
	outDev.displayStatus("Done!");
}
