#include "Bash.h"

Bash::Bash() :	
	currCommand(NULL),
	utils
	{
	"mv",       //cp + rm
	"rm",		//done
	"cp",
	"grep",
	"cd",		//done
	"ls",		//done
	"mkdir",	//done
	"touch",	//done
	"exit",		//done
	"clear"   //done
	},
	curPath("c:/Users/mrmih/")
{
}


Bash::~Bash()
{
	delete currCommand;
}

void Bash::getCommand() throw(BashErrInfo)
{

	exCmnd  action = no_command;
	std::string  command,
				 src,
				 dst;
	vector<std::string>::iterator v_command_iter;
	cin >> command;
	int cmdIndex = 0;

	for (v_command_iter = utils.begin();            //comparing command names
			v_command_iter != utils.end();
				v_command_iter++,cmdIndex++)
	{
		if (command.compare(*v_command_iter) == 0)
		{
			action = static_cast<exCmnd>(cmdIndex);
		}
	}
	if (action == no_command) throw BashErrInfo("Such command doesn't exist");

	switch (action)
	{
	case mv:
	{
		check();
		 
		break;
	}
	case rm:
	{
		cin >> dst;
		check();
		currCommand = new Remove(dst,curPath);	
		break;
	}
	case cp:
	{
		check();
		break;
	}
	case grep:
	{
		check();
		break;
	}
	case cd:
	{
		cin >> dst;
		check();
		currCommand = new ChangeDir(dst, curPath);
		break;
	}
	case ls:
	{
		check();
		currCommand = new ShowDir(curPath);
		break;
	}
	case makedir:
	{
		cin >> dst;
		check();
		currCommand = new MakeDir(dst,curPath);
		break;
	}
	case touch:
	{
		cin >> dst;
		check();
		currCommand = new Create_File(dst,curPath);
		break;
	}
	case ex_it:
	{
		check();
		exit(EXIT_SUCCESS);
		break;
	}
	case clearCon:
	{
		check();
		system("cls");
		break;
	}
	}
}



void Bash::execute()
{
	if(currCommand != NULL)
		currCommand->exec();
}

void Bash::setCurrPath(string cP)
{
	curPath = cP;
}

string Bash::getCurrPath()
{
	return curPath;
}

void Bash::check()
{
	if (currCommand != NULL)
	{
		delete currCommand;
		currCommand = NULL;
	}
		
}



