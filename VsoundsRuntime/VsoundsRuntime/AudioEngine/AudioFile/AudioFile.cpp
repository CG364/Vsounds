#include "AudioFile.h"

AudioFile::AudioFile(audiere::AudioDevicePtr deviceToPlayOn, std::string path)
{
	this->path = path;
	this->currentDevice = deviceToPlayOn;
}
AudioFile::~AudioFile()
{
	Free();
}


void AudioFile::Play()
{
	streamPtr = audiere::OpenSound(currentDevice, path.c_str(), true);
	streamPtr->setRepeat(0);
	streamPtr->play();
}

void AudioFile::Free()
{
	streamPtr = 0;
}


bool AudioFile::IsLive()
{
	return streamPtr->isPlaying();
}
