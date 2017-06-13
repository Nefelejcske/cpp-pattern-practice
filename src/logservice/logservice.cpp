#include <iostream>
#include "logservice.h"

LogService::LogService(): 
	stream(std::cout)
	, delimeter(" ")
	, lineend("\n\n")
{}
LogService::LogService(LogService& logservice): 
	stream(logservice.stream)
	, delimeter(logservice.delimeter)
	, lineend(logservice.lineend)
{}
LogService::LogService(std::ostream& stream): 
	stream(stream)
	, delimeter(" ")
	, lineend("\n\n")
{}
LogService::LogService(std::ostream& stream, const std::string& delimeter, const std::string& lineend): 
	stream(stream)
	, delimeter(delimeter)
	, lineend(lineend)
{}

void LogService::setDelimeter(const std::string& delimeter)
{
	this->delimeter = delimeter;
}

void LogService::setLineEnding(const std::string& lineend)
{
	this->lineend = lineend;
}
