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

	bool operator==(DeadBeef const& rhs) const
	{
		return id == rhs.id;
	}

private:
	unsigned id;
	static unsigned nextId;
	LogService log;
};

unsigned DeadBeef::nextId = 1;

int main(int argc, char const *argv[])
{
	LogService log {};
	log.info("\n_________________Starting Object Pool Example_________________");
	
	constexpr int SIZE = 80000;
	constexpr int ITERATIONS = 1;

	ObjectPool<DeadBeef, SIZE> pool {};

	std::vector<DeadBeef> items {};
	for (int i = 0; i < ITERATIONS; ++i)
	{
		log.info("Items Test", i);
		items = {};

		log.info("Add Items Test", i);
		for (int i = 0; i < SIZE; ++i)
		{
			items.push_back(pool.create());
		}
		log.info("Remove Items Test", i);
		for (auto i = items.begin(); i != items.end(); ++i)
		{
			pool.remove(*i);
		}
		log.info("Items Test", i, "Done");
	}

	return 0;
}