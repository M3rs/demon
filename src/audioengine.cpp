#include "audioengine.hpp"

#include "oneshot.hpp"
#include <iostream>

AudioEngine::AudioEngine()
	: m_studioSystem(nullptr), m_lowLevelSystem(nullptr),
	starcraftBank(nullptr), stringsBank(nullptr), masterBank(nullptr) {}

AudioEngine::~AudioEngine() {
  if (starcraftBank != NULL)
    starcraftBank->unload();
  if (stringsBank != NULL)
    stringsBank->unload();
  if (masterBank != NULL)
    masterBank->unload();
  // lowLevelSystem->release(); //releasing Studio seems to also release the low
  // level system
  if (m_studioSystem != NULL)
    m_studioSystem->release();
}

bool AudioEngine::initialize()
{
	result = FMOD::Studio::System::create(&m_studioSystem);
	if (result != FMOD_OK) {
		std::cout << "Error: Failed to create FMOD studio system instance."
			<< std::endl;
		std::cin.get();
		return false;
	}

	result = m_studioSystem->getLowLevelSystem(&m_lowLevelSystem);
	if (result != FMOD_OK) {
		std::cout << "Error: Could not get low level FMOD system." << std::endl;
		std::cin.get();
		return false;
	}

	result = m_lowLevelSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_STEREO, 0);
	if (result != FMOD_OK) {
		std::cout << "Error: Problem setting FMOD software format." << std::endl;
		std::cin.get();
		return false;
	}

	result = m_studioSystem->initialize(32, FMOD_STUDIO_INIT_NORMAL,
		FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK) {
		std::cout << "Error: Initialization of FMOD studio system instance could "
			"not be completed."
			<< std::endl;
		std::cin.get();
		return false;
	}

	result = m_studioSystem->loadBankFile(
		"Master Bank.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank);
	if (result != FMOD_OK) {
		std::cout << "Error: Master Bank file could not be located or loaded."
			<< std::endl;
		std::cin.get();
		return false;
	}

	result = m_studioSystem->loadBankFile(
		"Master Bank.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank);
	if (result != FMOD_OK) {
		std::cout << "Error: Strings Bank file could not be located or loaded."
			<< std::endl;
		std::cin.get();
		return false;
	}

	result = m_studioSystem->loadBankFile(
		"starcraft.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &starcraftBank);
	if (result != FMOD_OK) {
		std::cout << "Error: Starcraft bank could not be located or loaded."
			<< std::endl;
		std::cin.get();
		return false;
	}

	return true;
}

void AudioEngine::playOneShot(const std::string &eventPath) const {
	FMOD_RESULT result;
  FMOD::Studio::EventDescription *evtDesc(nullptr);
  result = m_studioSystem->getEvent(eventPath.c_str(), &evtDesc);
  if (result != FMOD_OK)
  {
	  std::cout << "Error starting oneshot from path: " << eventPath.c_str()
				<< std::endl;
	  return;
  }
  OneShot::Play(evtDesc);
}

void AudioEngine::update() { m_studioSystem->update(); }

void AudioEngine::loadBank(const std::string& path) {
	FMOD::Studio::Bank* bank(nullptr);
	result = m_studioSystem->loadBankFile(path.c_str(), 
		FMOD_STUDIO_LOAD_BANK_NORMAL, &bank);
	if (result != FMOD_OK) {
		std::cout << "Error loading bank path: '" << path << "'"
			<< std::endl;
	}
	else
		bankList.emplace(path, bank);
}

void AudioEngine::unloadBank(const std::string& path) {
	FMOD::Studio::Bank* bank(nullptr);
	result = m_studioSystem->getBank(path.c_str(), &bank);
	if (result != FMOD_OK) {
		std::cout << "Could not unload bank path: '" << path << "'"
			<< std::endl;
	}
	else { bankList.erase(path); }
}
