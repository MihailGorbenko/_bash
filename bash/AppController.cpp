#include "AppController.h"

AppController::AppController(){}

AppController::~AppController(){}

void AppController::execute() 
{

	while (true)
	{
		std::string info = "root@root: ";
		info += console.getCurrPath();
		info += ">";
		outpDev.displayInfo(info);
		try
		{
			console.getCommand();
			console.execute();
		}
		catch (BashErrInfo &ex)
		{
			outpDev.displayErr(ex.what());
			continue;
		}
	} 
}
