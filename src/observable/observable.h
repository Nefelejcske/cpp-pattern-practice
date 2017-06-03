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
	Observable(Observable const& observable);

	template<class Fun> int subscribe(Fun callback);
	void unsubscribe(int index);

private:
	Subject<T>& subject_;

	friend class Subject<T>;
};

template<class T>
Observable<T>::Observable(Subject<T>* subject): 
	subject_(*subject)
{}

template<class T>
Observable<T>::Observable(Observable const& observable): 
	subject_(observable.subject_)
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
