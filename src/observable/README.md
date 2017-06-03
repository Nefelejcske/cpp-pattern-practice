# Observable 

This is a basic implementation of the Observable pattern.

## Usage
### Example:
```c++
#include <iostream>
#include "subject.h"
#include "observable.h"

class SomeInteresting
{
public:
	SomeInteresting() {}

	Observable<int> onIncrement()
	{
		return subject_.asObservable();
	}
private:
	Subject<int> subject_;
};

.....


int main()
{
	auto interesting = SomeInteresting();
	int sub = interesting.onIncrement().subscribe([](int value){std::cout<<value;});
	interesting.onIncrement().unsubscribe(sub);
	return 0;
}
```