# Observable 

This is a basic implementation of the Observable pattern.

## Usage
### Idea
__Subject__ lets _Observers_ listen to events.<br>
__Observable__ is a proxy that can be exposed to listeners without exposing the rest of the __Subject__'s API (aka. next()).<br>
__Subscription__ lets us store callbacks.<br><br>
__*Subject callbacks*__ work with both _lambdas_, _function pointers_ and _functors_.

### Example
```cpp
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


```
This code outputs:
```
Info:
_____________Starting Observer Example_____________

Info:    Incrementing value 0
Info:    Listening to increment:  0
Info:    Incrementing value 1
Info:    Listening to increment:  1
Info:    Incrementing value 2
Info:    Incrementing value 3

```