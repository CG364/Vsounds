#include "KeyboardInputProvider.h"

KeyboardInputProvider::KeyboardInputProvider()
{
}

void KeyboardInputProvider::Init()
{
	
}

void KeyboardInputProvider::Bind(std::vector<SoundConfigItem> itemList) //start the windows message loop with the specified hotkeys
{
	this->itemList = itemList;
	
	messageThread = std::thread(&KeyboardInputProvider::messageThread_w, this);
}

void KeyboardInputProvider::Unbind()
{
	Logger::Log("Cleaning up the windows message loop...");
}

KeyboardInputProvider::~KeyboardInputProvider()
{

}

//code to communicate with windows
void KeyboardInputProvider::messageThread_w()
{
	//first register the hotkeys
	for (size_t i = 0; i < itemList.size(); i++)
	{
		bool res = RegisterHotKey(0, i, itemList[i].inputActivationMod, itemList[i].inputActivation);
		if (!res) { Logger::Log("Unable to register " + itemList[i].Path + ": " + std::to_string(GetLastError())); }
		registeredItems.push_back(itemList[i]);
	}
	bool res = RegisterHotKey(0, itemList.size(), 0x0001 | 0x4000, 0x1B); //escape key
	if (!res)
	{
		int err = GetLastError();
		wchar_t buf[256];
		FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, err, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buf, (sizeof(buf) / sizeof(wchar_t)), NULL);
		std::wstring errmsg(buf);
		throw new LoggedException("Unable to register the key combination ALT+ESC. Please ensure the key isn't being used by another application. Error code " + std::to_string(err) + ": " + std::string(errmsg.begin(), errmsg.end()));
	}
	//And now wait
	MSG incoming{};
	while (GetMessage(&incoming, 0, 0, 0))
	{
		switch (incoming.message)
		{
		case WM_HOTKEY:
		{
			int key = (incoming.lParam & 0x01FF0000) >> 16; //stole this code from my older c# app, will replace this with wParam and then find the ID instead of the key
			if (key == 27) //escape key
			{
				Logger::Log("ESC pressed, stopping all sounds.");
				for (size_t i = 0; i < AudioEngine::engineList.size(); i++)
				{
					AudioEngine::engineList[i]->stopAll();
				}
			}
			for (size_t i = 0; i < registeredItems.size(); i++)
			{
				if (key == registeredItems[i].inputActivation)
				{
					Logger::Log("Found key: " + registeredItems[i].Path);
					AudioEngine::engineList[0]->playSound(registeredItems[i].Path);
				}
			}
			
		}
		break;

		default:
			break;
		}
	}
}
