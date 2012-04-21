#pragma once

#include <SFML/Audio.hpp>
#include <stdio.h>

class SoundEngine 
{
public:
	SoundEngine();
	~SoundEngine();
	void Load_Jetpack();
	void Play_Jetpack(bool);
	void Load_Music();
	void Play_Music();
	void Stop_Music();
	bool jetpack_playing;
	
private:
	sf::Sound JetpackSound;
	sf::SoundBuffer JetpackBuffer;
	sf::Music Music1;
	sf::Sound::Status JetStatus;
};
