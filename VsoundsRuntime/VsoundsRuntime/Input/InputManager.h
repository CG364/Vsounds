#pragma once

#include "../includes.h"
#include "../Log/Logger.h"
#include "./Providers/KeyboardInputProvider.h"
class InputManager
{
public:
	InputManager();
	void AssignInputs(std::vector<SoundConfigItem> ListToLoad);
private:
	KeyboardInputProvider KeyboardIP;
};

