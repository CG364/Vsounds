#include "InputManager.h"

InputManager::InputManager()
{
	Logger::Log("Starting input manager");
}

void InputManager::AssignInputs(std::vector<SoundConfigItem> ListToLoad)
{
	std::vector<SoundConfigItem> keyboardList = Configuration::FilterSoundConfigurationVector(ListToLoad, INPUT_KEYBOARD);
	KeyboardIP.Bind(keyboardList);
}
