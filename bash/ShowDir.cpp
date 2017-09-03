#include "ShowDir.h"



ShowDir::ShowDir(const std::string ph) :path(ph) {}


ShowDir::~ShowDir()
{
}

void ShowDir::exec()
{
	_finddata_t *foundFile = new _finddata_t;

	int resultList,
		status;

	std::list<_finddata_t>             dirs;
	std::list<_finddata_t>::iterator   l_dirs_iter;
	std::string                        tempPath = path + "*.*";

	resultList = _findfirst(tempPath.c_str(), foundFile);
	status = resultList;

	while (status != -1)
	{
		if (strcmp(foundFile->name, ".") != 0 
			&& strcmp(foundFile->name, "..") != 0)
		{
			if (foundFile->attrib & _A_SUBDIR)
			{
				dirs.push_back(*foundFile);
			}
			else
				outp.displayFile(foundFile->name);
		}

		status = _findnext(resultList, foundFile);
	}

	for (l_dirs_iter = dirs.begin();
			l_dirs_iter != dirs.end();
				l_dirs_iter++)
	    {
			outp.displayDir(l_dirs_iter->name);
        }
	delete foundFile;
	_findclose(resultList);
}
