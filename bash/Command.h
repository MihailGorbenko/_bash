#pragma once
class Command
{
public:
	Command() {};
	~Command() {};
	virtual void exec() = 0;
};

