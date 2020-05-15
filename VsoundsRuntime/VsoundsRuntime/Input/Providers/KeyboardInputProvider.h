#pragma once

#include "../../includes.h"
#include "../../Config/Configuration.h"
#include "../../Log/Logger.h"
class KeyboardInputProvider
{
public:
	KeyboardInputProvider();
	void Init();
	void Bind(std::vector<SoundConfigItem> itemList);
	void Unbind();
	~KeyboardInputProvider();
private:
	std::vector<SoundConfigItem> itemList;
	void messageThread_w();
	std::thread messageThread;
	std::vector<SoundConfigItem> registeredItems;
};

