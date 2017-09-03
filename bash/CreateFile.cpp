#include "CreateFile.h"


Create_File::Create_File(std::string &dPh, std::string &curr):
	currPath(curr),
	destPath(dPh)
{
}


Create_File::~Create_File()
{
}

void Create_File::exec() throw(BashErrInfo)
{
	if (destPath.find('/') == std::string::npos)
	{
		currPath += destPath;
	}
	else if (destPath.find(':') != std::string::npos)
	{
		currPath = destPath;
	}

	if (_access(currPath.c_str(), 00) == 0)
	{
		throw BashErrInfo("Such file already exists!");
	}
	else
	{
		std::ofstream file(currPath, std::ios::out);
		if (!file) throw BashErrInfo("Can't create file!");

		file.close();
	}
}
