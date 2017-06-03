#include <iostream>
#include "command.h"
#include "../print/logservice.h"

class FirstCmd: public Command
{
public:
	FirstCmd(LogService& logService): logService_(logService){}

	virtual void execute()
	{
		logService_.info("First command executed!");
	}

private:
	LogService& logService_;
};

class SecondCmd: public Command
{
public:
	SecondCmd(LogService& logService): logService_(logService){}

	virtual void execute()
	{
		logService_.info("Second command executed!");
	}

private:
	LogService& logService_;
};

class ThirdCmd: public Command
{
public:
	ThirdCmd(LogService& logService): logService_(logService){}

	virtual void execute()
	{
		logService_.info("Third command executed!");
	}

private:
	LogService& logService_;
};

class SomeActor
{
public:
	~SomeActor()
	{
		delete first_;
		delete second_;
		delete third_;
	}

	SomeActor(LogService& log):
		logService(log)
		, first_(new FirstCmd(log))
		, second_(new SecondCmd(log))
		, third_(new ThirdCmd(log))
	{}
	
	Command* getCommand() const
	{
		static int callCount = 0;
		switch(callCount++ % 3)
		{
			case 0:
				return first_;
			case 1:
				return second_;
			default:
				return third_;
		}
	}

private:
	LogService& logService;
	FirstCmd* first_;
	SecondCmd* second_;
	ThirdCmd* third_;
};

int main(int argc, char const *argv[])
{
	auto logService = LogService();
	logService.info("\n_____________Starting_____________");
	auto actor = SomeActor(logService);
	logService.setLineEnding("\n");
	for(int i=0; i<10; ++i)
	{
		logService.debug("command:",i);
		auto cmd = actor.getCommand();
		cmd->execute();
	}
	return 0;
}