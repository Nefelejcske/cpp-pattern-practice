#include <iostream>
#include "core/subject.h"

class SomeInteresting
{
public:
	SomeInteresting(): current_(0) {}

	Observable<int> onIncrement()
	{
		return subject_.asObservable();
	}

	void increment()
	{
		std::cout<<"Incementing value:"<<current_<<"\n";
		subject_.next(current_++);
	}
private:
	Subject<int> subject_;
	int current_;
};

int main()
{
	auto interesting = SomeInteresting();
	int sub = interesting
		.onIncrement()
		.subscribe([](int value){
			std::cout<<"Listening to increment: "<<value<<'\n';
		});
	
	for (int i = 0; i < 2; ++i)
	{
		interesting.increment();
	}

	interesting.onIncrement().unsubscribe(sub);
	
	for (int i = 0; i < 2; ++i)
	{
		interesting.increment();
	}
	return 0;
}
