#include <iostream>
#ifndef LOGSERVICE
#define LOGSERVICE

#include <mutex>

class LogService 
{
public:
	LogService();
	LogService(std::ostream& stream);
	LogService(std::ostream& stream, const std::string& delimeter, const std::string& lineend);

	void setDelimeter(const std::string& delimeter);
	void setLineEnding(const std::string& lineend);
	
	template<class ...Args>	void info(Args const& ... args);
	template<class ...Args>	void debug(Args const& ... args);
	template<class ...Args>	void warn(Args const& ... args);
	template<class ...Args>	void error(Args const& ... args);
private:
	std::ostream& stream_;
	std::string delimeter_;
	std::string lineend_;
	std::mutex printMutex_;
	
	template<class T> void print(T const& item);
	template<class T, class ...Args> void print(T const& head, Args const& ... tail);
	template<class ...Args> void startPrint(Args const& ... tail);
};

template<class ...Args>
void LogService::error(Args const& ... args)
{
	startPrint("Error:\t", args...);
}

template<class ...Args>
void LogService::warn(Args const& ... args)
{
	startPrint("Warning:\t", args...);
}

template<class ...Args>
void LogService::debug(Args const& ... args)
{
	startPrint("Debug:\t", args...);
}

template<class ...Args>
void LogService::info(Args const& ... args)
{
	startPrint("Info:\t", args...);
}

template<class T>
void LogService::print(T const& item)
{
	stream_<<item<<lineend_;
}

template<class T, class ...Args>
void LogService::print(T const& head,Args const& ... tail)
{
	stream_<<head<<delimeter_;
	print(tail...);
}

template<class ...Args>
void LogService::startPrint(Args const& ...tail)
{
	std::lock_guard<std::mutex> lock (printMutex_);
	print(tail...);
}

#endif
