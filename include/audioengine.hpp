#ifndef AUDIOENGINE_HPP
#define AUDIOENGINE_HPP

#include <string>

namespace {
  class System;
  namespace {
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

  void update();

  bool errorcheck(FMOD_RESULT result_) const;

private:
  FMOD::Studio::System *m_studioSystem;
  FMOD::System *m_lowLevelSystem;

  FMOD_RESULT result;
};

#endif // AUDIOENGINE_HPP
