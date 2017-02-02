#include "oneshot.hpp"

OneShot::OneShot(const FMOD::Studio::EventDescription *description)
    : m_instance(nullptr) {
  description->createInstance(&m_instance);
  m_instance->start();
}
OneShot::~OneShot() {
  if (m_instance)
    m_instance->release();
}

void OneShot::Play(const FMOD::Studio::EventDescription *description) {
  auto sfx = OneShot(description);
}
