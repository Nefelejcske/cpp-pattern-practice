#include <iostream>
#include "logservice.h"

class ExampleType
{
public:
	friend std::ostream& operator <<(std::ostream& stream, const ExampleType& item)
	{
		stream<<"a_:["<<item.a_<<"], foo_:["<<item.foo_<<"]"<<", winnie:["<<item.winnie_<<"]";
		return stream;
	}

	ExampleType(): 
		a_(234)
		, foo_(345.8654)
		, winnie_("the pooh")
	{}

private:
	int a_;
	float foo_;
	std::string winnie_;
};

int main()
{
	LogService logService {};
	logService.info("\n___________________Starting LogService Example___________________");
	logService.warn(1, 1.6, "Hello");
	logService.debug("Here's a type: ", ExampleType());
	return 0;
}
