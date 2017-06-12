#ifndef SNYC_RESOURCE_H
#define SNYC_RESOURCE_H

#include <memory>
#include <shared_mutex>

namespace Job
{
	template<typename T>
	class SyncResource
	{
	public:
		SyncResource(T const& resource): 
			resource(std::make_unique<T>(resource)) 
		{}
		
		SyncResource(SyncResource& copy) = delete;

		virtual ~SyncResource(){}

		virtual T const& read()
		{
			std::shared_lock<std::shared_mutex> lock(mutex);
			return *resource;
		}

		virtual void write(T const& value)
		{
			std::lock_guard<std::shared_mutex> guard(mutex);
			resource = std::make_unique<T>(value);
		}
	protected:
		std::unique_ptr<T> resource;
		std::shared_mutex mutex;
	};
}

#endif
