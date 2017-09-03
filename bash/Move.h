#pragma once
#include "Command.h"

enum moveObj
{
	File,
	Dir
};

class Move :
	public Command
{
public:
	Move(const char *from,const char *to,moveObj obj);
	~Move();
	void exec();
};

