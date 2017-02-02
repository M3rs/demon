#ifndef STARCRAFT_ONESHOT_HPP
#define STARCRAFT_ONESHOT_HPP

#include "fmod_studio.hpp"

class OneShot {
public:
  OneShot(const FMOD::Studio::EventDescription *desciption);
  ~OneShot();

  static void Play(const FMOD::Studio::EventDescription *desciption);

private:
  FMOD::Studio::EventInstance* m_instance; 
};

#endif // STARCRAFT_ONESHOT_HPP
