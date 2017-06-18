#ifndef POOL_ITEM_H
#define POOL_ITEM_H

#include <iostream>
#include "iterable_pool.h"

template<class T, unsigned size>
class PoolItem: public T
{
public:
	PoolItem() {}
	virtual ~PoolItem() {}

	T& getItem()
	{
		return *this;
	}

	unsigned getIndex() { return poolIndex; }
	
	void setIndex(unsigned value) { poolIndex = value; }

private:
	unsigned poolIndex;

	friend std::ostream& operator << (std::ostream& stream, PoolItem<T, size> const& item);
};

template<class T, unsigned size>
std::ostream& operator << (std::ostream& stream, PoolItem<T, size> const& item)
{
	stream<<"Item: "<<item.getItem()<<"\nIndex: "<<item.poolIndex;
	return stream;
}

#endif
