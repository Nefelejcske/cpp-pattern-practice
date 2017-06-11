#include <iostream>
#include <thread>

#include <unistd.h>

#include "../../logservice/logservice.h"
#include "../core/resource.h"

class JobChain
{
public:
	JobChain(Job::SyncResource<int>& src, LogService& log, std::string name): 
		resource_(src), log_(log), name_(name)
	{}
	~JobChain(){}

	void operator()()
	{
		unsigned limit = 3;
		while(limit--)
		{
			auto current = resource_.read();
			log_.info(name_, '#', 3-limit, "first read", current++);
			usleep(5000);
			resource_.write(current);
			log_.info(name_, '#', 3-limit, "second read", resource_.read());
		}
	}
private:
	Job::SyncResource<int>& resource_;
	LogService& log_;
	std::string name_;
};

int main(int argc, char const *argv[])
{
	LogService log {};
	log.info("\n__________Starting Thread Example__________");

	Job::SyncResource<int> src (1);
	auto chain1 = JobChain(src, log, "T1");
	auto chain2 = JobChain(src, log, "T2");
	auto chain3 = JobChain(src, log, "T3");
	std::thread t1 (chain1);	
	std::thread t2 (chain2);	
	std::thread t3 (chain3);	
	t1.join();
	t2.join();
	t3.join();
	log.info("\n__________Ending Thread Example__________");
	return 0;
}
