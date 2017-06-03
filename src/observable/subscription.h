#ifndef SUBCRIPTION_H
#define SUBCRIPTION_H

template<class T>
class ISubscription
{
public:
	virtual ~ISubscription(){}
	virtual void operator()(T arg) = 0;
};

template<class T, class Fun>
class Subscription: public ISubscription<T>
{
public:
	Subscription(Fun const& callback): callback_(callback){}

	virtual void operator()(T arg)
	{
		callback_(arg);
	}
private:
	Fun callback_;	
};

#endif
