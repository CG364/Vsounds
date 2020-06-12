#include "Logger.h"
void Logger::Log(std::string logString, std::string funcName,int type )
{
	auto startTime = std::chrono::high_resolution_clock::now();
	while (IsLogging)
	{
		auto stopTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = stopTime - startTime;
		double elapsedTime = elapsed.count();
		if (elapsedTime > 0.010)
		{
			std::cout << "\nTimed out waiting for thread " << std::ios::hex << threadLockedID << " to finish writing to console(" << elapsedTime << " s).";
			break;
		}
	}
	threadLockedID = (UINT)GetCurrentThread();
	IsLogging = true;
	std::cout << type << ", " <<  funcName <<": " << logString << "\n";
	IsLogging = false;
}

volatile bool Logger::IsLogging = false;
int Logger::threadLockedID = 0;