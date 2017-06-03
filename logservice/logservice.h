#include <iostream>
#ifndef LOGSERVICE
#define LOGSERVICE

class LogService 
{
public:
	LogService();
	LogService(std::ostream& stream);
	LogService(std::ostream& stream, const std::string& delimeter, const std::string& lineend);

	void setDelimeter(const std::string& delimeter);
	void setLineEnding(const std::string& lineend);
	
	template<class ...Args>	void info(Args const& ... args) const;
	template<class ...Args>	void debug(Args const& ... args) const;
	template<class ...Args>	void warn(Args const& ... args) const;
	template<class ...Args>	void error(Args const& ... args) const;
private:
	std::ostream& stream_;
	std::string delimeter_;
	std::string lineend_;
	
	template<class T> void print(T const& item) const;
	template<class T, class ...Args> void print(T const& head, Args const& ... tail) const;
};

template<class ...Args>
void LogService::error(Args const& ... args) const
{
	print("Error:\t", args...);
}

template<class ...Args>
void LogService::warn(Args const& ... args) const
{
	print("Warning:\t", args...);
}

template<class ...Args>
void LogService::debug(Args const& ... args) const
{
	print("Debug:\t", args...);
}

template<class ...Args>
void LogService::info(Args const& ... args) const
{
	print("Info:\t", args...);
}

template<class T>
void LogService::print(T const& item) const
{
	stream_<<item<<lineend_;
}

template<class T, class ...Args>
void LogService::print(T const& head,Args const& ... tail) const
{
	stream_<<head<<delimeter_;
	print(tail...);
}

#endif
