#pragma once

#include "Command.h"
#include "BashExeptions.h"

#include <string>
#include <io.h>
#include <iostream>
#include <fstream>


	class Create_File :
		public Command
	{
	public:
		Create_File(std::string &, std::string &);
		~Create_File();
		void exec() throw (BashErrInfo);
	private:
		std::string destPath,
					currPath;
	};



