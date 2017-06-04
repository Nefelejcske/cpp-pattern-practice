# Observable 

This is a basic implementation of the Observable pattern.

## Usage
### Idea
__Subject__ lets _Observers_ listen to events.<br>
__Observable__ is a proxy that can be exposed to listeners without exposing the rest of the __Subject__'s API (aka. next()).<br>
__Subscription__ lets us store callbacks.<br>
__Subject__ _callbacks_ work with both _lambda_-s, _function pointer_-s and _functor_-s.

### Example
```cpp

#include <iostream>
#include "subject.h"
#include "observable.h"

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
	
	for (int i = 0; i < 5; ++i)
	{
		interesting.increment();
	}

	interesting.onIncrement().unsubscribe(sub);
	
	for (int i = 0; i < 5; ++i)
	{
		interesting.increment();
	}
	return 0;
}

```
This code outputs:
```

Incementing value:0
Listening to increment: 0
Incementing value:1
Listening to increment: 1
Incementing value:2
Listening to increment: 2
Incementing value:3
Listening to increment: 3
Incementing value:4
Listening to increment: 4
Incementing value:5
Incementing value:6
Incementing value:7
Incementing value:8
Incementing value:9

```