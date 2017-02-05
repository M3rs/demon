#include "audioengine.hpp"
#include "fmod_errors.h"
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
	if (errorcheck(result) != FMOD_OK)
		return false;

	result = m_studioSystem->getLowLevelSystem(&m_lowLevelSystem);
	if (errorcheck(result) != FMOD_OK)
		return false;

	result = m_lowLevelSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_STEREO, 0);
	if (errorcheck(result) != FMOD_OK)
		return false;

	result = m_studioSystem->initialize(32, FMOD_STUDIO_INIT_NORMAL,
		FMOD_INIT_NORMAL, 0);
	if (errorcheck(result) != FMOD_OK)
		return false;

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
  if (errorcheck(result) != FMOD_OK)
	  return;
  //OneShot::Play(evtDesc); //deprecated
  FMOD::Studio::EventInstance* evtInst;
  result = evtDesc->createInstance(&evtInst);
  if (errorcheck(result) != FMOD_OK)
	  return;
  evtInst->start();
  evtInst->release();
}

void AudioEngine::playOneShotWithParameter(
	const std::string& eventPath, 
	const std::string& paramName, 
	float paramValue)
{
	FMOD_RESULT result;
	FMOD::Studio::EventDescription *evtDesc(nullptr);
	result = m_studioSystem->getEvent(eventPath.c_str(), &evtDesc);
	if (errorcheck(result) != FMOD_OK)
		return;
	FMOD::Studio::EventInstance *evtInst(nullptr);
	result = evtDesc->createInstance(&evtInst);
	if (errorcheck(result) != FMOD_OK)
		return;
	result = evtInst->setParameterValue(paramName.c_str(), paramValue);
	if (errorcheck(result) != FMOD_OK)
		return;
	evtInst->start();
	evtInst->release();
	return;
}

void AudioEngine::update() { m_studioSystem->update(); }

bool AudioEngine::loadBank(const std::string& path) {
	FMOD::Studio::Bank* bank(nullptr);
	result = m_studioSystem->loadBankFile(path.c_str(), 
		FMOD_STUDIO_LOAD_BANK_NORMAL, &bank);
	if (errorcheck(result) != FMOD_OK)
		return false;
	return true;
}

bool AudioEngine::unloadBank(const std::string& path) {
	FMOD::Studio::Bank* bank(nullptr);
	result = m_studioSystem->getBank(path.c_str(), &bank);
	if (errorcheck(result) != FMOD_OK)
		return false;	
	else { 
		result = bank->unload();
		if (errorcheck(result) != FMOD_OK)
			return false;
	}
	return true;
}

FMOD_RESULT AudioEngine::errorcheck(FMOD_RESULT result_) const{
	//let calling function decide what to do with FMOD_RESULT
	//use FMOD error codes to determine what went wrong if there's an error
	if (result_ != FMOD_OK) 
		std::cout << "FMOD error: " << FMOD_ErrorString(result_) << std::endl;
	return result_;
}
