#pragma once
#include "./includes.h"
#include "./Log/Logger.h"
#include "./AudioEngine/AudioEngine.h"
#include "./Config/Configuration.h"
#include "./Input/InputManager.h"
//This program requires:
//nlohmann:json https://github.com/nlohmann/json
//Audiere(tmp): http://audiere.sourceforge.net/


static int filterException(int code, PEXCEPTION_POINTERS ex) {
    std::cout << "Uncaught structured exception: " << std::hex << code;
    terminate();
    return EXCEPTION_EXECUTE_HANDLER;
}

void mainCaught();

int main()
{
    __try 
    {

        mainCaught();

    }
    __except (filterException(GetExceptionCode(), GetExceptionInformation()))
    {
        
        terminate();
    }
}

void mainCaught()
{
    Logger::Log("Vsounds - CG364 (Compiled on " + std::string(__DATE__) + " at " + std::string(__TIME__) + ")");

    AudioEngine* AE = new AudioEngine(""); 

    std::vector<SoundConfigItem> confList = Configuration::GetSoundConfigurationVector(); //read the sound configuration;
    confList = Configuration::GetSoundConfigurationVector();
    InputManager man = {}; //create a inputmanager instance
    man.AssignInputs(confList);//and assign the inputs

    while (true)
    {
        Sleep(5000); //this thread will become the notification tray icon / will communicate with windows.
    }
}
