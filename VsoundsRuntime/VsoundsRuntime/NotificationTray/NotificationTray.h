#pragma once
#include "../includes.h"
#include "../Log/Logger.h"
class NotificationTray
{
public:
	void Start();
	void Stop();
private:
	void work(); //message loop
	HWND NotificationWindow;
	int callbackMessage;

};

