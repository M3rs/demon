#include "audioengine.hpp"

#include "fmod_errors.h"
#include <iostream>

namespace {

// return true if no error
bool errorcheck(FMOD_RESULT result_) {
  if (result_ != FMOD_OK) {
    std::cout << "FMOD error: " << FMOD_ErrorString(result_) << std::endl;
    return false;
  }

  return true;
}
}

AudioEngine::AudioEngine()
    : m_studioSystem(nullptr), m_lowLevelSystem(nullptr) {}

AudioEngine::~AudioEngine() {

  // https://www.fmod.org/docs/content/generated/FMOD_Studio_System_Release.html
  // According to docs, "This will free the Studio System object and everything created under it."
  if (m_studioSystem != NULL)
    m_studioSystem->release();
}

bool AudioEngine::initialize() {
  auto result = FMOD::Studio::System::create(&m_studioSystem);
  if (!errorcheck(result))
    return false;

  result = m_studioSystem->getLowLevelSystem(&m_lowLevelSystem);
  if (!errorcheck(result))
    return false;

  result = m_lowLevelSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_STEREO, 0);
  if (!errorcheck(result))
    return false;

  result = m_studioSystem->initialize(32, FMOD_STUDIO_INIT_NORMAL,
                                      FMOD_INIT_NORMAL, 0);
  if (!errorcheck(result))
    return false;

  if (!(loadBank("res/banks/Master bank.bank")))
    return false;

  if (!(loadBank("res/banks/Master bank.strings.bank")))
    return false;

  if (!(loadBank("res/banks/starcraft.bank")))
    return false;

  if (!(loadBank("res/banks/player.bank")))
    return false;

  return true;
}

void AudioEngine::playOneShot(const std::string &eventPath) const {
  FMOD::Studio::EventDescription *evtDesc(nullptr);
  auto result = m_studioSystem->getEvent(eventPath.c_str(), &evtDesc);
  if (!errorcheck(result))
    return;
  // OneShot::Play(evtDesc); //deprecated
  FMOD::Studio::EventInstance *evtInst;
  result = evtDesc->createInstance(&evtInst);
  if (!errorcheck(result)) {
    evtInst->release();
    return;
  }
  evtInst->start();
  evtInst->release();
}

void AudioEngine::playOneShotWithParameter(const std::string &eventPath,
                                           const std::string &paramName,
                                           float paramValue) {
  FMOD::Studio::EventDescription *evtDesc(nullptr);
  auto result = m_studioSystem->getEvent(eventPath.c_str(), &evtDesc);
  if (!errorcheck(result))
    return;
  FMOD::Studio::EventInstance *evtInst(nullptr);
  result = evtDesc->createInstance(&evtInst);
  if (!errorcheck(result))
    return;
  result = evtInst->setParameterValue(paramName.c_str(), paramValue);
  if (!errorcheck(result)) {
    evtInst->release();
    return;
  }

  evtInst->start();
  evtInst->release();
  return;
}

void AudioEngine::update() { m_studioSystem->update(); }

bool AudioEngine::loadBank(const std::string &path) {
  FMOD::Studio::Bank *bank(nullptr);
  auto result = m_studioSystem->loadBankFile(
      path.c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &bank);
  if (!errorcheck(result))
    return false;
  return true;
}

bool AudioEngine::unloadBank(const std::string &path) {
  FMOD::Studio::Bank *bank(nullptr);
  auto result = m_studioSystem->getBank(path.c_str(), &bank);
  if (!errorcheck(result))
    return false;
  else {
    result = bank->unload();
    if (!errorcheck(result))
      return false;
  }
  return true;
}

void AudioEngine::playEvent(const std::string &path) {
	auto it = events_cache.find(path);
	if (it != events_cache.end()) {
		auto evt = it->second;
		evt->start();
	}
	FMOD::Studio::EventDescription *evtDesc(nullptr);
	auto result = m_studioSystem->getEvent(path.c_str(), &evtDesc);
	if (!errorcheck(result))
		return;
	FMOD::Studio::EventInstance *evtInst(nullptr);
	result = evtDesc->createInstance(&evtInst);
	if (!errorcheck(result))
		return;
	events_cache.emplace(path, std::move(evtInst));
	evtInst->start();
}

void AudioEngine::stopEvent(const std::string &path, FMOD_STUDIO_STOP_MODE stopMode) {
	auto it = events_cache.find(path);
	if (it != events_cache.end()) {
		auto evt = it->second;
		evt->stop(stopMode);
	}
}