#include "Logger.h"
void Logger::Log(std::string logString, int type)
{
	while (IsLogging);
	IsLogging = true;
	std::cout << type << ": " << logString << "\n";
	IsLogging = false;
}

volatile bool Logger::IsLogging = false;