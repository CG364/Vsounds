#include "Configuration.h"

//A static function that reads the configuration file, parses the contents and returns a vector of configured sounds.
//It also caches the vector so it doesnt have to read the file all the time.
std::vector<SoundConfigItem> Configuration::GetSoundConfigurationVector(bool refreshCache)
{
	if(cacheIsFilled && !refreshCache)
	{
		return cache;
	}
	else
	{
		std::string confFilePath = std::string(std::getenv("APPDATA")) + "\\Vsounds\\config.json";
		Logger::Log("Importing sound configuration from: " + confFilePath);
		std::ifstream fileStream = std::ifstream(confFilePath, std::ios::binary);

		auto deserializedJson = nlohmann::json::parse(fileStream);
		int configItemsCount = deserializedJson.size();

		std::vector<SoundConfigItem>confList;
		for (size_t i = 0; i < configItemsCount; i++)
		{
			SoundConfigItem curr_item = {};
			curr_item.inputType = INPUT_KEYBOARD;
			curr_item.inputActivation = deserializedJson[i]["ActivationKey"];
			curr_item.inputActivationMod = deserializedJson[i]["ActivationModifierKey"];
			curr_item.Name = (std::string)deserializedJson[i]["Name"].get<std::string>();
			curr_item.Path = (std::string)deserializedJson[i]["DefaultPath"].get<std::string>();
			confList.push_back(curr_item);
		}
		Logger::Log("Configuration imported. " + std::to_string(confList.size()) + " Elements found.");
		cache = confList;
		cacheIsFilled = true;
		return confList;
	}

	
}

//this function will filter the sound config vector to only contain the input type that is relevant.
std::vector<SoundConfigItem> Configuration::FilterSoundConfigurationVector(std::vector<SoundConfigItem> originalVec, int inputType)
{
	std::vector<SoundConfigItem> filtered;
	for (size_t i = 0; i < originalVec.size(); i++)
	{
		if (originalVec[i].inputType == inputType)
		{
			filtered.push_back(originalVec[i]);
		}
	}
	return filtered;
}

//gets a string value from a given application rule
std::string Configuration::getApplicationConfigRuleS(std::string rule)
{
	return std::string();
}

//gets a boolean value from a given application rule
bool Configuration::getApplicationConfigRulesB(std::string rule)
{
	return false;
}

//gets a int value from a given application rule
int Configuration::getApplicationConfigRulesI(std::string rule)
{
	return 0;
}

bool Configuration::cacheIsFilled;
std::vector<SoundConfigItem> Configuration::cache;