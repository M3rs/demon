#ifndef AUDIOENGINE_HPP
#define AUDIOENGINE_HPP

#include "fmod_studio.hpp"
#include <iostream>

#include <string>

class AudioEngine {
public:
	AudioEngine();
	~AudioEngine();

	//void loadBank(const std::string& path);	//will make more sophisticated
												//bank loading behavior later

	//void unloadBank(const std::string& path);

	void playOneShot(const std::string& path);

	void update();

private:
	FMOD::Studio::System*	m_studioSystem;
	FMOD::System*			m_lowLevelSystem;
	FMOD::Studio::Bank*		masterBank;
	FMOD::Studio::Bank*		stringsBank;
	FMOD::Studio::Bank*		starcraftBank;

	FMOD_RESULT				result;

};


#endif // AUDIOENGINE_HPP
