#pragma once
#include "Bash.h"
#include "Display.h"
#include "BashExeptions.h"

class AppController
{
public:
	AppController();
	~AppController();
	void execute();
private:
	Bash      console;
	Display   outpDev;
};

