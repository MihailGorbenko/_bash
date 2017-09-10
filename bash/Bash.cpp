#include "Bash.h"

Bash::Bash() :	
	currCommand(NULL),
	curPath("c:/Users/mrmih/")
{
	
	std::fstream uNames("utils.txt", std::ios::in);
	if (!uNames) exit(EXIT_FAILURE);
	std::string temp;
	while (!uNames.eof())
	{
		getline(uNames, temp);
		utils.push_back(temp);
	}
}


Bash::~Bash()
{
	if(currCommand != NULL)
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
	if (action == no_command)
	{
		std::string trash;
		getline(cin, trash);
		throw BashErrInfo("Such command doesn't exist");
	}

	switch (action)
	{
	case mv:
	{
		std::cin >> src >> dst;
		check();
		Copy * cp = new Copy(src, dst,curPath);
		cp->exec();
		currCommand = new Remove(src,curPath);
		delete cp;
		break;
	}
	case rm:
	{
		std::cin >> dst;
		check();
		currCommand = new Remove(dst,curPath);	
		break;
	}
	case cp:
	{
		std::cin >> src >> dst;
		check();
		currCommand = new Copy(src, dst,curPath);
		break;
	}
	case _find:
	{
		cin >> src;
		check();
		currCommand = new Find( src,curPath);
		break;
	}
	case cd:
	{
		std::cin >> dst;
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
		std::cin >> dst;
		check();
		currCommand = new MakeDir(dst,curPath);
		break;
	}
	case touch:
	{
		std::cin >> dst;
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
	case re_name:
	{
		std::cin >> src>>dst;
		check();
		currCommand = new Rename(src, dst, curPath);
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



