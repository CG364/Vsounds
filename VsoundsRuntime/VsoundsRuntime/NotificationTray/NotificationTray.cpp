#include "NotificationTray.h"

void NotificationTray::Start() //uses calling thread
{
	this->NotificationWindow = CreateWindowA("VSNUTWINDOW", "Vsounds notification icon receiver", WS_VISIBLE, 0,0,100,100, 0, 0, 0, 0);

	NOTIFYICONDATAA nutData = {};
	nutData.cbSize = sizeof(NOTIFYICONDATAA);
	nutData.uFlags = NIF_TIP | NIF_SHOWTIP | NIF_MESSAGE | NIF_GUID | NIF_ICON;
	nutData.hIcon = LoadIcon(GetModuleHandle(0), MAKEINTRESOURCE(VS_ICON));
	nutData.hWnd = this->NotificationWindow;
	nutData.uCallbackMessage = 420;
	if (!Shell_NotifyIconA(NIM_ADD, &nutData)) 
	{
		int err = GetLastError();
		DebugBreak();
	}
	
	this->work();
}

void NotificationTray::work()
{
	while (1)
	{
		
		MSG message;
		GetMessageW(&message, this->NotificationWindow, 0, 0);
		
		switch (message.message)
		{
		case 420:
			Logger::Log("message from notifyicon", __FUNCTION__);
			break;
		default:
			break;
		}
	}
}
