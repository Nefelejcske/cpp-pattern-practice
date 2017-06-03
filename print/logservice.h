#include <iostream>
#ifndef LOGSERVICE
#define LOGSERVICE

class LogService
{
public:
	LogService();
	LogService(std::ostream& stream);
	LogService(std::ostream& stream, const std::string& delimeter);

	void setDelimeter(const std::string& delimeter);
	
	template<class ...Args>	void info(Args... args);
	template<class ...Args>	void debug(Args... args);
	template<class ...Args>	void warn(Args... args);
	template<class ...Args>	void error(Args... args);
private:
	std::ostream& stream_;
	std::string delimeter_;
	
	template<class T>
	void print(T item);
	
	template<class T, class ...Args>
	void print(T head, Args... tail);
};

template<class ...Args>
void LogService::error(Args... args)
{
	print("Error:\t", args...);
}

template<class ...Args>
void LogService::warn(Args... args)
{
	print("Warning:\t", args...);
}

template<class ...Args>
void LogService::debug(Args... args)
{
	print("Debug:\t", args...);
}

template<class ...Args>
void LogService::info(Args... args)
{
	print("Info:\t", args...);
}

template<class T>
void LogService::print(T item)
{
	stream_<<item<<"\n\n";
}

template<class T, class ...Args>
void LogService::print(T head, Args... tail)
{
	stream_<<head<<delimeter_;
	print(tail...);
}

#endif
