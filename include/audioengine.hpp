#ifndef AUDIOENGINE_HPP
#define AUDIOENGINE_HPP

#include "fmod_studio.hpp"

class AudioEngine {
public:
	AudioEngine();
	~AudioEngine();

	void loadBank(string path);

	void loadAllBanks();

	void unloadBank(string path);

	void unloadAllBanks();



private:
	FMOD::Studio::System*	m_studioSystem;
	FMOD::System*			m_lowLevelSystem;
	FMOD::Studio::Bank*		masterBank;
	FMOD::Studio::Bank*		stringsBank;
	FMOD::Studio::Bank*		starcraftBank;

	FMOD_RESULT				result;

};


#endif // AUDIOENGINE_HPP
