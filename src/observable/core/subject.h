#ifndef SUBJECT_H
#define SUBJECT_H

#ifndef OBSERVABLE_H
	template<class T> class Subject;
#endif

#include <memory>
#include <algorithm>
#include "observable.h"

template<class T>
class Subject
{
public:
	Subject();
	Subject(Subject<T> const& subject);
	virtual ~Subject(){}

	void next(T const& nextValue);
	Observable<T>& asObservable();

	template<class Fun> int subscribe(Fun callback);
	void unsubscribe(int index);
private:
	std::vector<std::shared_ptr<ISubscription<T> > > subscriptions;
	std::unique_ptr<Observable<T> > observable;
};

template<typename T>
Subject<T>::Subject(): observable(new Observable<T>(this))
{}

template<typename T>
Subject<T>::Subject(Subject<T> const& subject): 
	observable(new Observable<T>(this))
	, subscriptions(subject.subscriptions)
{}

template<typename T>
void Subject<T>::next(T const& nextValue)
{
	for(auto sub : subscriptions)
	{
		(*sub)(nextValue);
	}
}

template<typename T>
Observable<T>& Subject<T>::asObservable()
{
	return *observable;
}

template<class T>
template<class Fun> 
int Subject<T>::subscribe(Fun callback)
{
	auto ptr = std::make_shared<Subscription<T, Fun> >(callback);
	int result = subscriptions.size();
	subscriptions.push_back(ptr);
	return result;
}

template<class T>
void Subject<T>::unsubscribe(int index)
{
	subscriptions
		.erase(
			std::remove(
				subscriptions.begin()
				, subscriptions.end()
				, subscriptions[index]
			)
			, subscriptions.end()
		);
}

#endif