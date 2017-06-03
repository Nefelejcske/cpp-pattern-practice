#include <iostream>
#include "logservice.h"

LogService::LogService(): 
	stream_(std::cout)
	, delimeter_(" ")
{}
LogService::LogService(std::ostream& stream): 
	stream_(stream)
	, delimeter_(" ")
{}
LogService::LogService(std::ostream& stream, const std::string& delimeter): 
	stream_(stream)
	, delimeter_(delimeter)
{}

void LogService::setDelimeter(const std::string& delimeter)
{
	delimeter_ = delimeter;
}