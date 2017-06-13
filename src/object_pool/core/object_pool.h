#ifndef OBJECT_POOL_H_0xdeadbeef
#define OBJECT_POOL_H_0xdeadbeef

#include <memory>
#include <cassert>
#include <array>

template<class T, unsigned size>
class ObjectPool
{
public:
	ObjectPool();
	virtual ~ObjectPool();

	T& create();
	bool remove(T& item);
protected:
	std::array<T, size> pool;
	unsigned next;
private:
	void swapItems(unsigned index1, unsigned index2);
};

template<class T, unsigned size>
ObjectPool<T, size>::ObjectPool(): next(0) {}

template<class T, unsigned size>
ObjectPool<T, size>::~ObjectPool(){}

template<class T, unsigned size>
T& ObjectPool<T, size>::create()
{
	return pool[next++];
}

template<class T, unsigned size>
bool ObjectPool<T, size>::remove(T& item)
{
	for (int i = 0; i < next; ++i)
	{
		if(item == pool[i])
		{
			swapItems(i, --next);
			return true;
		}
	}
	assert(false);
}

template<class T, unsigned size>
void ObjectPool<T, size>::swapItems(unsigned index1, unsigned index2)
{
	assert(index1 < size);
	assert(index2 < size);
	using std::swap;
	swap(pool[index1], pool[index2]);
}

#endif
