#pragma once
#include "../includes.h";
class Logger
{
public:
	static void Log(std::string logString, std::string funcName,int type = 0);
private:
	static int GetConsoleColor(int logType);
	static void ChangeConsoleColor(int color);
	static volatile bool IsLogging;

};

