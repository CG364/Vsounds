#pragma once
#include "./includes.h"
#include "./Log/Logger.h"
#include "./AudioEngine/AudioEngine.h"
#include "./Config/Configuration.h"
#include "./Input/InputManager.h"
#include "./NotificationTray/NotificationTray.h"
//This program requires:
//nlohmann:json https://github.com/nlohmann/json
//Audiere(tmp): http://audiere.sourceforge.net/

LPEXCEPTION_POINTERS exceptionInfo;
static int filterException(int code, LPEXCEPTION_POINTERS ex) {
    exceptionInfo = ex;
    return EXCEPTION_EXECUTE_HANDLER;
}

bool doContinueApplication = true;
void mainCaught();

void quitApplication()
{
    Logger::Log("Quitting Vsounds...", __FUNCTION__, 2);
    doContinueApplication = false;
}


int main()
{
   
    __try 
    {

        mainCaught();

    }
    __except (filterException(GetExceptionCode(), GetExceptionInformation()))
    {
        PEXCEPTION_RECORD excRec = exceptionInfo->ExceptionRecord;
        std::cout << "\n\nFATAL EXCEPTION:\n";
        std::cout << "\nException code: " << excRec->ExceptionCode << " at " << std::ios::hex << excRec->ExceptionAddress;
        terminate();
    }
}

void mainCaught()
{
    Logger::Log("Vsounds - CG364 (Compiled on " + std::string(__DATE__) + " at " + std::string(__TIME__) + ")", __FUNCTION__);

    AudioEngine* AE = new AudioEngine(""); 

    std::vector<SoundConfigItem> confList = Configuration::GetSoundConfigurationVector(); //read the sound configuration;

    confList = Configuration::GetSoundConfigurationVector();
    InputManager man = {}; //create a inputmanager instance
    man.AssignInputs(confList);//and assign the inputs
    NotificationTray* trayIcon = new NotificationTray();
    trayIcon->Start();
}
