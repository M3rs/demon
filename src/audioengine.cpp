#include "audioengine.hpp"

#include "oneshot.hpp"
#include <iostream>

AudioEngine::AudioEngine()
	: m_studioSystem(nullptr), m_lowLevelSystem(nullptr),
	starcraftBank(nullptr), stringsBank(nullptr), masterBank(nullptr) {}

AudioEngine::~AudioEngine() {
	unloadBank("player.bank");
	unloadBank("starcraft.bank");
	unloadBank("Master bank.strings.bank");
	unloadBank("Master bank.bank");
	
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

	if (!(loadBank("Master bank.bank")))
		return false;

	if (!(loadBank("Master bank.strings.bank")))
		return false;

	if (!(loadBank("starcraft.bank")))
		return false;

	if (!(loadBank("player.bank")))
		return false;

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

void AudioEngine::playOneShotWithParameter(
	const std::string& eventPath, 
	const std::string& paramName, 
	float paramValue)
{
	FMOD_RESULT result;
	FMOD::Studio::EventDescription *evtDesc(nullptr);
	result = m_studioSystem->getEvent(eventPath.c_str(), &evtDesc);
	if (result != FMOD_OK)
	{
		std::cout << "Error starting oneshot from path: " << eventPath.c_str()
			<< std::endl;
		return;
	}
	FMOD::Studio::EventInstance *evtInst(nullptr);
	result = evtDesc->createInstance(&evtInst);
	if (result != FMOD_OK) {
		std::cout << "Error creating instance from EvtDesc" << eventPath.c_str()
			<< std::endl;
		return;
	}
	result = evtInst->setParameterValue(paramName.c_str(), paramValue);
	if (result != FMOD_OK) {
		std::cout << "Error setting parameter " << paramName.c_str() <<
			" -- check that the Event has this parameter defined." << std::endl;
		return;
	}
	evtInst->start();
	evtInst->release();
	return;
}

void AudioEngine::update() { m_studioSystem->update(); }

bool AudioEngine::loadBank(const std::string& path) {
	FMOD::Studio::Bank* bank(nullptr);
	result = m_studioSystem->loadBankFile(path.c_str(), 
		FMOD_STUDIO_LOAD_BANK_NORMAL, &bank);
	if (result != FMOD_OK) {
		std::cout << "Error loading bank path: '" << path << "'"
			<< std::endl;
		return false;
	}
	return true;
}

bool AudioEngine::unloadBank(const std::string& path) {
	FMOD::Studio::Bank* bank(nullptr);
	result = m_studioSystem->getBank(path.c_str(), &bank);
	if (result != FMOD_OK) {
		std::cout << "Could not get bank path for unload: '" << path << "'"
			<< " - this bank may already be unloaded." << std::endl;
		return false;
	}
	
	else { 
		result = bank->unload();
		if (result != FMOD_OK) {
			std::cout << "Could not unload bank path: '" << path << "'"
				<< std::endl;
			return false;
		}	
	}
	return true;
}
