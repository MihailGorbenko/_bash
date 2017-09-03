#pragma once
#include <string>

class BashErrInfo
{
public:
	BashErrInfo(std::string msg) : exeptMsg(msg) {};
	~BashErrInfo() {};
	std::string what()const
	{
		return exeptMsg;
	};
private:
	std::string exeptMsg;
};

