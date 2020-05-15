#include "AudioEngine.h"
AudioEngine::AudioEngine(std::string sDevice = "")
{
	currentDevice = audiere::OpenDevice(0, 0);
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

void AudioEngine::EnumerateDevices()
{

}

void AudioEngine::GarbageCollectorWork()
{
	Logger::Log("Starting garbage collector thread");
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
			Logger::Log("Gargbage collector - " + std::to_string(RemovedItems) + " items freed.");
		}
		Sleep(5000);
	}
}

bool AudioEngine::mfStartup = false;

std::vector<AudioEngine*> AudioEngine::engineList;