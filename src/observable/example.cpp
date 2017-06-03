#include <iostream>
#include "subject.h"
#include "observable.h"
#include "../logservice/logservice.h"

struct Subscriber
{
public:
	Subscriber(LogService const& logger): logger(LogService()){}
	
	void operator()(int value)
	{
		logger.info("Functor win!", value);
	}

private:
	LogService logger;
};

void callback(int value)
{
	std::cout<<"Callback win! "<<value<<"\n\n";
}

int main(int argc, char const *argv[])
{
	auto logger = LogService();
	logger.info("___________Starting Observable Example___________");
	auto subject = new Subject<int>();
	
	subject->asObservable()
		.subscribe([&](int value){
			logger.info("Lambda win! ", value);
		});
	
	auto subscriber = Subscriber(logger);
	subject->asObservable().subscribe(subscriber);
	
	subject->asObservable().subscribe(*(callback));
	
	subject->next(5);
	delete subject;
	
	logger.info("Bye!");
	return 0;	
}
