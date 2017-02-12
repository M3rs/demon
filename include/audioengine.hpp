#ifndef AUDIOENGINE_HPP
#define AUDIOENGINE_HPP

#include <string>
#include <map>
#include "fmod_studio.hpp"

// fwds
namespace FMOD {
  class System;
  namespace Studio {
    class System;
  }
}

class AudioEngine {
public:
  AudioEngine();
  ~AudioEngine();

  bool initialize();

  bool loadBank(const std::string &path);

  // TODO: do something with return value
  bool unloadBank(const std::string &path);

  void playOneShot(const std::string &path) const;

  void playOneShotWithParameter(const std::string &eventPath,
                                const std::string &paramName, float paramValue);

  void playEvent(const std::string &path);

  void stopEvent(const std::string &path, FMOD_STUDIO_STOP_MODE stopMode);

  void update();

private:
  FMOD::Studio::System *m_studioSystem;
  FMOD::System *m_lowLevelSystem;

  //cache of persistent events (music, mixer snapshots) that can be
  //manually controlled via other audioengine functions
  std::map<std::string, FMOD::Studio::EventInstance*> events_cache;
};

#endif // AUDIOENGINE_HPP
