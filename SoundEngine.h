#include <SFML/Audio.hpp>

class SoundEngine
{
	sf::SoundBuffer JetpackSound;
	sf::SoundBuffer JetpackBuffer;
	
	void Load_Jetpack();
	void Play_Jetpack();
	void Stop_Jetpack();
}