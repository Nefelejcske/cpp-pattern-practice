#include <iostream>

#include "core/iterable_pool.h"
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

	friend std::ostream& operator<<(std::ostream& ostream, DeadBeef const& beef);
};

std::ostream& operator<<(std::ostream& ostream, DeadBeef const& beef)
{
	ostream<<"DeadBeef#"<<beef.id;
	return ostream;
}

unsigned DeadBeef::nextId = 1;

int main(int argc, char const *argv[])
{
	LogService log {};
	log.info("\n_________________Starting Object Pool Example_________________");
	
	constexpr int SIZE = 10;
	constexpr int ITERATIONS = 5;

	IterablePool<DeadBeef, SIZE> pool {};

	std::vector<DeadBeef> items {};
	for (int w = 1; w <= ITERATIONS; ++w)
	{
		log.info("_______________Items Test", w, "_______________");
		items = {};

		log.info("Add Items Test", w);
		for (int i = 0; i < SIZE; ++i)
		{
			auto & beef = pool.create();
			log.debug("Created beef: ", beef);
			items.push_back(beef);
		}

		log.info("Iterate Active Items Test", w);
		pool.iterateActive([&](auto & beef){
			log.debug("Calling beef: ", beef);
		});

		log.info("Remove Items Test", w);
		for (auto i = items.begin(); i != items.end(); ++i)
		{
			log.debug("Removing beef: ", *i);
			pool.remove(*i);
		}
		log.info("_______________Items Test", w, "Done_______________");
	}

	return 0;
}
