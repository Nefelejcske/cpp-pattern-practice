#include <iostream>

#include "core/object_pool.h"
#include "../logservice/logservice.h"

#include <memory>
#include <vector>

class DeadBeef
{
public:
	DeadBeef(): id(nextId++), log() {}	

	DeadBeef(DeadBeef const& beef): id(beef.id), log() {}

	~DeadBeef() {}
	
	DeadBeef& operator=(DeadBeef const& beef)
	{
		id = beef.id;
		return *this;
	}

	bool operator==(DeadBeef const& rhs)
	{
		return id == rhs.id;
	}

	unsigned id;
private:
	static unsigned nextId;
	LogService log;
};

unsigned DeadBeef::nextId = 1;

int main(int argc, char const *argv[])
{
	LogService log {};
	log.info("\n_________________Starting Object Pool Example_________________");
	
	ObjectPool<DeadBeef, 20000> pool {};

	std::vector<DeadBeef> items {};
	for (int i = 0; i < 20000; ++i)
	{
		items.push_back(pool.create());
	}
	for (auto i = items.begin(); i != items.end(); ++i)
	{
		pool.remove(*i);
	}
	return 0;
}