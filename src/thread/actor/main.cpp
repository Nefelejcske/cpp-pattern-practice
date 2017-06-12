#include <iostream>
#include <thread>
#include <memory>
#include <vector>
#include <cassert>

#include "../core/actor.h"
#include "../../logservice/logservice.h"

class Comedian: public Actor
{
public:
	Comedian(LogService& logService, std::string name): 
		logService(logService)
		, name(name)
		, isSlapped{false, false}
	{}

	~Comedian(){}

	virtual void update()
	{
		if(isSlapped[index])
		{
			logService.info(name, "was slapped! Slapping", target->getName());
			target->slap();
			isSlapped[index] = false;
		}
	}

	void slap()
	{
		isSlapped[1 - index] = true;
	}

	std::string& getName()
	{
		assert(this != 0x00);
		return name;
	}

	void setTarget(std::shared_ptr<Comedian> comedian)
	{
		target = comedian;
	}

	static void swap()
	{
		index = 1 - index;
	}
private:
	static int index;

	LogService& logService;	
	std::string name;
	bool isSlapped[2];
	std::shared_ptr<Comedian> target;
};

int Comedian::index = 0;

std::vector<std::shared_ptr<Comedian> > setStage(LogService& log)
{
	auto comedian1 = std::make_shared<Comedian>(log, "Comedian1");
	auto comedian2 = std::make_shared<Comedian>(log, "Comedian2");
	auto comedian3 = std::make_shared<Comedian>(log, "Comedian3");
	auto comedian4 = std::make_shared<Comedian>(log, "Comedian4");

	comedian1->setTarget(comedian2);
	comedian2->setTarget(comedian3);
	comedian3->setTarget(comedian4);
	comedian4->setTarget(comedian1);

	comedian1->slap();
	comedian1->swap();

	return std::vector<std::shared_ptr<Comedian> > {comedian1, comedian2, comedian3, comedian4};
}

void updateStage(std::vector<std::shared_ptr<Comedian> > comedians)
{
	std::vector<std::thread> threads {};
	for(auto & comedian: comedians)
	{
		threads.push_back(std::thread([&]{comedian->update();}));
	}
	for(auto & thread: threads)
	{
		thread.join();
	}
	Comedian::swap();
}

int main(int argc, char const *argv[])
{
	LogService log {};
	log.info("____________Starting Actor Example____________");
	
	auto stage = setStage(log);

	unsigned limit = 5;
	while(limit--)
	{
		log.info("Starting update", 5 - limit);
		updateStage(stage);
	}

	return 0;
}