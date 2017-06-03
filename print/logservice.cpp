#include <iostream>
#include "logservice.h"

LogService::LogService(): 
	stream_(std::cout)
	, delimeter_(" ")
	, lineend_("\n\n")
{}
LogService::LogService(std::ostream& stream): 
	stream_(stream)
	, delimeter_(" ")
	, lineend_("\n\n")
{}
LogService::LogService(std::ostream& stream, const std::string& delimeter, const std::string& lineend): 
	stream_(stream)
	, delimeter_(delimeter)
	, lineend_(lineend)
{}

void LogService::setDelimeter(const std::string& delimeter)
{
	delimeter_ = delimeter;
}

void LogService::setLineEnding(const std::string& lineend)
{
	lineend_ = lineend;
}
