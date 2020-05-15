#pragma once
#include "./AudioFile/AudioFile.h"
#include "../includes.h"
#include "../Log/Logger.h"
class AudioFile;
class AudioEngine
{
public:
	AudioEngine(std::string sDevice);
	void playSound(std::string Path);
	void stopAll();
	void stopId(int id);
	bool CollectGarbage = true;
	static void EnumerateDevices();
	static std::vector<AudioEngine*> engineList;

private:
	audiere::AudioDevicePtr currentDevice;
	std::vector<AudioFile*> PlayingFileList;
	std::thread GarbageCollectorThread;
	void GarbageCollectorWork();
	static bool mfStartup;

};

