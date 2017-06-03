#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#ifndef SUBJECT_H
	template<class T> class  ISubscription;
	template<class T, class Fun> class  Subscription;
	template<class T> class  Observable;
#endif

#include <vector>
#include <memory>
#include "subject.h"
#include "subscription.h"

template<class T>
class Observable
{
public:
	Observable(Subject<T>* subject);

	template<class Fun> int subscribe(Fun callback);
	void unsubscribe(int index);

private:
	std::vector<std::shared_ptr<ISubscription<T> > > subscriptions;
	Subject<T>& subject_;

	friend class Subject<T>;
};

template<class T>
Observable<T>::Observable(Subject<T>* subject): 
subscriptions()
, subject_(*subject)
{}

template<class T>
template<class Fun> 
int Observable<T>::subscribe(Fun callback)
{
	return subject_.subscribe(callback);
}

template<class T>
void Observable<T>::unsubscribe(int index)
{
	subject_.unsubscribe(index);
}

#endif
