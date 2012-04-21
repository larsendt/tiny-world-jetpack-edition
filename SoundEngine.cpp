#include "SoundEngine.h"

void SoundEngine::Load_Jetpack()
{
	if (!JetpackBuffer.LoadFromFile("sounds/jetpack_noise.wav"))
		{
			
		}
	JetpackSound.SetBuffer(JetpackBuffer);
	JetpackSound.SetLoop(true);
}

void SoundEngine::Play_Jetpack()
{
	JetpackSound.Play();
}

void SoundEngine::Stop_Jetpack()
{
	JetpackSound.Stop();
}

void SoundEngine::Load_Music()
{
	if (!Music1.OpenFromFile("sounds/music.mp3"))
		{
			// Error...
		}
	Music1.SetLoop(true);
}
void SoundEngine::Play_Music()
{
	Music1.Play();
}
void SoundEngine::Stop_Music()
{
	Music1.Pause();
}


SoundEngine::SoundEngine()
{}

SoundEngine::~SoundEngine()
{}