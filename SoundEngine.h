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
	bool jetpack_playing;
	
	void Load_WinMusic();
	void Play_WinMusic();
	void Pause_WinMusic();
	void Kill_WinMusic();
	
	void Load_AmbientMusic();
	void Play_AmbientMusic();
	void Pause_AmbientMusic();
	void Kill_AmbientMusic();
	
	
private:
	sf::Sound JetpackSound;
	sf::SoundBuffer JetpackBuffer;
	sf::Music Music1;
	sf::Music Music2;
	sf::Music Music3;
	sf::Music Music4;
	
	
	sf::Sound::Status JetStatus;
};
