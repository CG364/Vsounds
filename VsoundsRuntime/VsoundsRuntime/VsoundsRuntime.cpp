#pragma once
#include "./includes.h"
#include "./Log/Logger.h"
#include "./AudioEngine/AudioEngine.h"
#include "./Config/Configuration.h"
#include "./Input/InputManager.h"

void DisplayError(DWORD NTStatusMessage)
{
    LPVOID lpMessageBuffer;
    HMODULE Hand = LoadLibrary(L"NTDLL.DLL");

    FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER |FORMAT_MESSAGE_FROM_SYSTEM |FORMAT_MESSAGE_FROM_HMODULE, Hand, NTStatusMessage, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMessageBuffer, 0, NULL);

    // Now display the string.
    std::cout << lpMessageBuffer;
    // Free the buffer allocated by the system.
    LocalFree(lpMessageBuffer);
    FreeLibrary(Hand);
}

static int filterException(int code, PEXCEPTION_POINTERS ex) {
    std::cout << "Uncaught structured exception: " << std::hex << code;

    std::cout << "\nCannot handle, Aborting...";
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

    std::vector<SoundConfigItem> confList = Configuration::GetSoundConfigurationVector();
    confList = Configuration::GetSoundConfigurationVector();
    throw 0;
    
    InputManager man = {};
    man.AssignInputs(confList);

    while (true)
    {
        Sleep(5000); //this thread will become the notification tray icon / will communicate with windows.
    }
}
