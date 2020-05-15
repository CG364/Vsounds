#pragma once
#include "../includes.h"
#include "../AudioEngine/AudioFile/AudioFile.h";
#include "../Log/Logger.h"
#include "json.hpp"
class SoundConfigItem
{
public:
	int inputType;
	int inputActivation;
	int inputActivationMod;
	std::string Name;
	std::string Path;

};
class Configuration
{
public:
	static std::vector<SoundConfigItem> GetSoundConfigurationVector(bool refreshCache = false);
	static std::vector<SoundConfigItem> FilterSoundConfigurationVector(std::vector<SoundConfigItem> originalVec, int inputType);
	static std::string getApplicationConfigRuleS(std::string rule);
	static bool getApplicationConfigRulesB(std::string rule);
	static int getApplicationConfigRulesI(std::string rule);

private:
	static std::vector<SoundConfigItem> cache;
	static bool cacheIsFilled;
};

