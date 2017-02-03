#include "audioengine.hpp"
#include <iostream>

AudioEngine::AudioEngine()
	:	m_studioSystem(nullptr),
		m_lowLevelSystem(nullptr),
		starcraftBank(nullptr),
		stringsBank(nullptr),
		masterBank(nullptr)
{
	result = FMOD::Studio::System::create(&m_studioSystem);
	if (result != FMOD_OK) {
		std::cout << "Error: Failed to create FMOD studio system instance."
			<< std::endl;
		std::cin.get();
	}

	result = m_studioSystem->getLowLevelSystem(&m_lowLevelSystem);
	if (result != FMOD_OK) {
		std::cout << "Error: Could not get low level FMOD system." << std::endl;
		std::cin.get();
	}

	result = m_lowLevelSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_STEREO, 0);
	if (result != FMOD_OK) {
		std::cout << "Error: Problem setting FMOD software format." << std::endl;
		std::cin.get();
	}

	result = m_studioSystem->initialize(32, FMOD_STUDIO_INIT_NORMAL,
		FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK) {
		std::cout << "Error: Initialization of FMOD studio system instance could "
			"not be completed."
			<< std::endl;
		std::cin.get();
	}
}

AudioEngine::~AudioEngine()
{
	//lowLevelSystem->release(); //releasing Studio seems to also release the low level system
	if (m_studioSystem != NULL)
		m_studioSystem->release();
	unloadAllBanks();
}

void unloadAllBanks()
{
	if (starcraftBank != NULL)
		starcraftBank->unload();
	if (stringsBank != NULL)
		stringsBank->unload();
	if (masterBank != NULL)
		masterBank->unload();
}


