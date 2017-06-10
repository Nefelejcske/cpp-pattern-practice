#include <iostream>
#include "core/subject.h"
#include "../logservice/logservice.h"

class SomeInteresting
{
public:
	SomeInteresting(LogService& ls): logService_(ls), current_(0) {}

	Observable<int> onIncrement()
	{
		return subject_.asObservable();
	}

	void increment()
	{
		logService_.info("Incrementing value", current_);
		subject_.next(current_++);
	}
private:
	Subject<int> subject_;
	int current_;
	LogService& logService_;
};

int main()
{
	auto logService = LogService();
	logService.info("\n_____________Starting Observer Example_____________");
	logService.setLineEnding("\n");

	auto interesting = SomeInteresting(logService);
	int sub = interesting
		.onIncrement()
		.subscribe([&](int value){
			logService.info("Listening to increment: ", value);
		});
	
	for (int i = 0; i < 2; ++i) interesting.increment();
	interesting.onIncrement().unsubscribe(sub);
	for (int i = 0; i < 2; ++i) interesting.increment();

	return 0;
}
