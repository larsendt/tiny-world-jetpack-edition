#pragma once

#include <SFML/Audio.hpp>

class SoundEngine
{
public:
		SoundEngine();
		~SoundEngine();
	sf::Sound JetpackSound;
	sf::SoundBuffer JetpackBuffer;
	
	void Load_Jetpack();
	void Play_Jetpack();
	void Stop_Jetpack();
};