#include "AudioEngine.h"
//The audio engine class manages audio playback on a audio output device.
//the audiere library is temporarily used, but this will later be done with the Windows Media Foundation(i just want it to work first).
AudioEngine::AudioEngine(std::string sDeviceName = "")
{
	Logger::Log("", __FUNCTION__);
	if (sDeviceName == "")
	{
		
		currentDevice = audiere::OpenDevice(0, 0);
		
	}
	else
	{
		currentDevice = audiere::OpenDevice(sDeviceName.c_str(), 0);
	}
	if (!currentDevice)
	{
		throw new LoggedException("Audiere::OpenDevice() returned nullptr");
	}
	GarbageCollectorThread = std::thread(&AudioEngine::GarbageCollectorWork, this);
	engineList.push_back(this);
}

void AudioEngine::playSound(std::string Path)
{
	AudioFile* f = new AudioFile(currentDevice, Path);
	f->Play();
	PlayingFileList.push_back(f);
	
}

void AudioEngine::stopAll()
{
	int count = PlayingFileList.size();

	for (size_t i = 0; i < count; i++)
	{
		PlayingFileList[i]->Free();
		delete PlayingFileList[i];
	}
	PlayingFileList.clear();
}

void AudioEngine::EnumerateDevices()//reserved for later use
{

}

//this thread removes items that are finished playing from the live file list
void AudioEngine::GarbageCollectorWork()
{
	Logger::Log("Starting garbage collector thread", __FUNCTION__);
	while (CollectGarbage)
	{
		int RemovedItems = 0;
		for (size_t i = 0; i < PlayingFileList.size(); i++)
		{
			if (!PlayingFileList[i]->IsLive())
			{
				PlayingFileList[i]->Free();
				PlayingFileList.erase(PlayingFileList.begin() + i);
				RemovedItems++;
				i--;
			}
		}
		if (RemovedItems > 0)
		{
			Logger::Log("Gargbage collector - " + std::to_string(RemovedItems) + " items freed.", __FUNCTION__);
		}
		Sleep(5000);
	}
}

bool AudioEngine::mfStartup = false;

std::vector<AudioEngine*> AudioEngine::engineList;