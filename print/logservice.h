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
	
	template<class ...Args>	void info(Args const& ... args);
	template<class ...Args>	void debug(Args const& ... args);
	template<class ...Args>	void warn(Args const& ... args);
	template<class ...Args>	void error(Args const& ... args);
private:
	std::ostream& stream_;
	std::string delimeter_;
	
	template<class T> void print(T const& item);
	template<class T, class ...Args> void print(T const& head, Args const& ... tail);
};

template<class ...Args>
void LogService::error(Args const& ... args)
{
	print("Error:\t", args...);
}

template<class ...Args>
void LogService::warn(Args const& ... args)
{
	print("Warning:\t", args...);
}

template<class ...Args>
void LogService::debug(Args const& ... args)
{
	print("Debug:\t", args...);
}

template<class ...Args>
void LogService::info(Args const& ... args)
{
	print("Info:\t", args...);
}

template<class T>
void LogService::print(T const& item)
{
	stream_<<item<<"\n\n";
}

template<class T, class ...Args>
void LogService::print(T const& head,Args const& ... tail)
{
	stream_<<head<<delimeter_;
	print(tail...);
}

#endif
