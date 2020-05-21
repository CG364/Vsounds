#include "Logger.h"
void Logger::Log(std::string logString, std::string funcName,int type )
{
	while (IsLogging);
	IsLogging = true;
	std::cout << type << ", " <<  funcName <<": " << logString << "\n";
	IsLogging = false;
}

volatile bool Logger::IsLogging = false;