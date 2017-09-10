#define _CRT_SECURE_NO_WARNINGS
#include "Copy.h"



Copy::Copy(const std::string &src, const std::string &dst, const std::string &curr) :
	srcPath(src),
	dstPath(dst),
	currPath(curr)
{
}


Copy::~Copy()
{
}

void Copy::exec()throw (BashErrInfo)
{
	FILE * test;

	if (srcPath.find('/') == std::string::npos)   //if relative path
	{
		srcPath = currPath + srcPath;
	}
	if (dstPath.find('/') == std::string::npos) // if relative path
	{
		dstPath = currPath + dstPath;
	}
	if (_access(srcPath.c_str(), 00) == -1) throw BashErrInfo("Wrong source path!");

	try
	{
		if (srcPath.find(".", srcPath.rfind('/')) != std::string::npos)    //is file with extention
		{
			copyFile(srcPath, dstPath,false,false);     
		}

		else if ((test = fopen(srcPath.c_str(), "r")) != NULL)              //is file
		{
			fclose(test);                                     
			copyFile(srcPath, dstPath,false,false);
		}
		else
		{
			recCopy(srcPath, dstPath);                          //is dir
		}
	}
	catch (dirStat err)
	{
		static int index = 0;
		switch (err)
		{
		case existFile:
		{
			char answ;
			outDev.displayErr("Such file already exists,do you want to rewrite this?(y , n)");
			std::cin >> answ;

			while (true)
			{
				if (answ == 'y' || answ == 'Y')
				{
					try
					{
						copyFile(srcPath, dstPath,true,false);
					}
					catch (dirStat err)
					{
						outDev.displayErr("Can't copy >");
						outDev.displayStatus("from >" + srcPath + " to > " + dstPath);
					}
					break;
				}
				else if (answ == 'n' || answ == 'N')
				{
					char tempBuff[20];
					int index = 1;
					std::string curFname = srcPath.substr(srcPath.rfind('/') + 1);
					std::string tempDestPath = dstPath + '/' + curFname;
					while (_access(tempDestPath.c_str(),00) == 0)
					{
						std::string tempS;
						int dotPos = curFname.find('.');
						if ( dotPos != std::string::npos)
						{
							if (isdigit(curFname.at(curFname.find('.') - 1)))
							{
								curFname.at(curFname.find('.') - 1) = _itoa(index, tempBuff, 10)[0];
							}
							else
							{
								curFname = curFname.substr(0, curFname.find('.')) +_itoa(index, tempBuff, 10) +
																					curFname.substr(curFname.find('.'));
							}			
						}
						else
						{
							curFname += _itoa(index, tempBuff, 10);
						}
						tempDestPath = dstPath + '/' + curFname;
						index++;
					}

					try
					{
						copyFile(srcPath, tempDestPath ,false,true);
					}
					catch (dirStat err)
					{
						outDev.displayErr("Can't copy >");
						outDev.displayStatus("from >" + srcPath + " to > " + dstPath);
					}

					break;
				}
				outDev.displayErr("Wrong input!");
			}
			break;
		}
		case CannotOpen_r:
		{
			std::string msg = "Cannot open src file for reading!";
			outDev.displayErr(msg);
			break;
		}
		case CannotOpen_w:
		{
			std::string msg = "Cannot open dst file for writing!";
			break;
		}
		case CannotClose:
		{
			outDev.displayErr("Some problem with closing files!");
			break;
		}
		}
	}
}

void Copy::recCopy(std::string  src, std::string dst)
{
	_finddata_t found;
	long resList;
	int status;
	
	std::string dirName = src.substr(src.rfind('/'));
	outDev.displayStatus("Copying... from >" + src + " to > " + dst);
	if (_mkdir((dst += dirName).c_str()) == -1)
	{
		outDev.displayErr("Cannot create folder >" + dst);
		return;
	}

	resList = _findfirst((src + "/*.*").c_str(), &found);
		status = resList;
		
		while (status != -1)
		{
			if (strcmp(found.name, ".") !=0 && strcmp(found.name, "..") !=0)
			{
				if (found.attrib & _A_SUBDIR)
				{
					std::string tempS = src + '/' + found.name;
					_mkdir(dst.c_str());
					recCopy(tempS, dst);
				}
				else
				{
					std::string tempP = src + '/' + found.name;
					copyFile(tempP, dst,false,false);
				}
			}
			status = _findnext(resList, &found);
		}
		_findclose(resList);
		outDev.displayStatus("Done!");
	}
	

void Copy::copyFile(std::string  src, std::string  dst,bool nothrow, bool withFname) throw (dirStat)
{
	
	outDev.displayStatus("Copying... from > " + src + " to >" + dst);
	
	if (!withFname)
	{
		int slash = src.rfind('/');
		std::string fName = src.substr(slash);
		dst += fName;
	} 
	if (!nothrow)
	{
		if (_access(dst.c_str(), 00) == 0) throw existFile;
	}
	
	FILE * in = fopen(src.c_str(), "r");
	FILE *out = fopen(dst.c_str(), "w");

	if (in == NULL) throw CannotOpen_r;
	if (out == NULL) throw CannotOpen_w;

	int handle = _fileno(in);
	long fLen = _filelength(handle);

	char * buff = new char[fLen];
	fread(buff, sizeof(char), fLen, in);
	fwrite(buff, sizeof(char), fLen, out);

	if (fclose(in) == EOF || fclose(out) == EOF) throw CannotClose;
	outDev.displayStatus("Done!");
}
 