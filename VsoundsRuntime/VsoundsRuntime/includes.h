#pragma once
#include <iostream>
#include "audiere.h"
#include <wrl.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
#include <thread>
#include "windows.h"


//File types
#define FILETYPE_RIFF 1
#define FILETYPE_VORBIS 2
#define FILETYPE_MPEG_L3 3

//Input types
#define INPUT_KEYBOARD 1
#define INPUT_XINPUT 2



class LoggedException : std::exception
{
public:
	LoggedException(std::string exceptionText) { std::cout << "\nException thrown: " << exceptionText << "\n"; std::terminate(); };
};