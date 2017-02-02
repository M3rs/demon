#ifndef STARCRAFT_ONESHOT_HPP
#define STARCRAFT_ONESHOT_HPP

#include "fmod_studio.hpp"

class OneShot {
public:
  OneShot(const FMOD::Studio::EventDescription *description);
  ~OneShot();

  static void Play(const FMOD::Studio::EventDescription *description);

private:
  FMOD::Studio::EventInstance* m_instance; 
};

#endif // STARCRAFT_ONESHOT_HPP
