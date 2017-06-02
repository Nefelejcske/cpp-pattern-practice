#include <iostream>

class LogService
{
public:
	LogService();
	LogService(std::ostream& stream);

	template<class ...Args>
	void error(Args... args);

	template<class ...Args>
	void warn(Args... args);

	template<class ...Args>
	void debug(Args... args);

	template<class ...Args>
	void info(Args... args);

private:
	std::ostream& stream_;
	
	template<class T>
	void print(T item);
	
	template<class T, class ...Args>
	void print(T head, Args... tail);
};

LogService::LogService(): stream_(std::cout){}
LogService::LogService(std::ostream& stream): stream_(stream){}

template<class ...Args>
void LogService::error(Args... args)
{
	print("Error: ", args...);
}

template<class ...Args>
void LogService::warn(Args... args)
{
	print("Warning: ", args...);
}

template<class ...Args>
void LogService::debug(Args... args)
{
	print("Debug: ", args...);
}

template<class ...Args>
void LogService::info(Args... args)
{
	print("Info: ", args...);
}

template<class T>
void LogService::print(T item)
{
	stream_<<item<<'\n';
}

template<class T, class ...Args>
void LogService::print(T head, Args... tail)
{
	stream_<<head<<", ";
	print(tail...);
}
