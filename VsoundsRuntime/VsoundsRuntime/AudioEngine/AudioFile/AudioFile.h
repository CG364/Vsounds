#pragma once
#include "../../includes.h"
#include "../AudioEngine.h"
class AudioFileDetails;
class AudioFile
{
public:
	AudioFile(audiere::AudioDevicePtr deviceToPlayOn, std::string path);
	~AudioFile();
	bool IsLive();
	void Play();
	void Free();
private:
	std::string path;
	audiere::AudioDevicePtr currentDevice;
	audiere::OutputStreamPtr streamPtr;


};

