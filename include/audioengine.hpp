#ifndef AUDIOENGINE_HPP
#define AUDIOENGINE_HPP

#include "fmod_studio.hpp"
#include <iostream>
#include <map>

#include <string>

class AudioEngine {
public:
	AudioEngine();
	~AudioEngine();

	bool initialize();

	bool loadBank(const std::string& path);

	//TODO: do something with return value
	bool unloadBank(const std::string& path); 

	void playOneShot(const std::string& path) const;

	void playOneShotWithParameter(
		const std::string& eventPath,
		const std::string& paramName,
		float paramValue);

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
