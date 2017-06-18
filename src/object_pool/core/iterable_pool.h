#ifndef OBJECT_POOL_H_0xdeadbeef
#define OBJECT_POOL_H_0xdeadbeef

#include <memory>
#include <cassert>
#include <array>

#ifndef POOL_ITEM_H
template<class T, unsigned size> class IterablePool;
#endif

#include "pool_item.h"

template<class T, unsigned size>
class IterablePool
{
public:
	IterablePool();
	virtual ~IterablePool();

	T& create();
	bool remove(T& item);

	template<typename Fun> void iterateActive(Fun&& callback);
protected:
	std::array<PoolItem<T, size> , size> pool;
	unsigned next;
private:
	void swapItems(unsigned index1, unsigned index2);
};

template<class T, unsigned size>
IterablePool<T, size>::IterablePool(): next(0) 
{
	for (int i = 0; i < size; ++i) pool[i].setIndex(i);
}

template<class T, unsigned size>
IterablePool<T, size>::~IterablePool() {}

template<class T, unsigned size>
T& IterablePool<T, size>::create()
{
	assert(next < size);
	auto & result = pool[next++].getItem();
	return result;
}

template<class T, unsigned size>
bool IterablePool<T, size>::remove(T& item)
{
	auto index = static_cast<PoolItem<T, size>*>(&item)->getIndex();
	--next;
	if(index < next) swapItems(index, next);
	return true;
}

template<class T, unsigned size>
void IterablePool<T, size>::swapItems(unsigned index1, unsigned index2)
{
	assert(index1 < size);
	assert(index2 < size);
	using std::swap;
	swap(pool[index1], pool[index2]);
	pool[index2].setIndex(index2);
	pool[index1].setIndex(index1);
}

template<class T, unsigned size>
template<typename Fun> 
void IterablePool<T, size>::iterateActive(Fun&& callback)
{
	for (int i = 0; i < next; ++i) callback(pool[i].getItem());
}

#endif
