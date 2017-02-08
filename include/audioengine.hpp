#ifndef AUDIOENGINE_HPP
#define AUDIOENGINE_HPP

#include <string>

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

  void update();

private:
  FMOD::Studio::System *m_studioSystem;
  FMOD::System *m_lowLevelSystem;
};

#endif // AUDIOENGINE_HPP
