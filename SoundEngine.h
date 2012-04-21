#pragma once

#include <SFML/Audio.hpp>
#include <stdio.h>

class SoundEngine 
{
public:
	SoundEngine();
	~SoundEngine();
	void Load_Jetpack();
	void Play_Jetpack();
	void Stop_Jetpack();
	void Load_Music();
	void Play_Music();
	void Stop_Music();
	
private:
	sf::Sound JetpackSound;
	sf::SoundBuffer JetpackBuffer;
	sf::Music Music1;
};
