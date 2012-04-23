#include "SoundEngine.h"
#include <iostream>

void SoundEngine::Load_Jetpack()
{
	if (!JetpackBuffer.LoadFromFile("sounds/jetpack_noise.wav"))
		{
			
		}
	JetpackSound.SetBuffer(JetpackBuffer);
	JetpackSound.SetLoop(true);
	JetpackSound.SetVolume(20);
	jetpack_playing = false;
}

void SoundEngine::Play_Jetpack(bool is_playing)
{
	
/*	if (is_playing)
		{
		JetpackSound.Play();
		}*/
	
	JetStatus = JetpackSound.GetStatus();
	if (is_playing && (!jetpack_playing))
		{
		jetpack_playing = true;
		JetpackSound.Play();
		}
	
	else if (is_playing && jetpack_playing)
		{}
	
	else if (!is_playing && jetpack_playing)
		{
		JetpackSound.Stop();
		jetpack_playing = false;
		}
		
	else if (!is_playing && !jetpack_playing)
		{}
}

void SoundEngine::Load_Music()
{
	if (!Music1.OpenFromFile("sounds/win.ogg"))
		{
			// Error...
		}
	Music1.SetLoop(true);
}
void SoundEngine::Play_Music()
{
	Music1.Play();
}
void SoundEngine::Pause_Music()
{
	Music1.Pause();
}
void SoundEngine::Kill_Music()
{
	Music1.Stop();
}


SoundEngine::SoundEngine()
{}

SoundEngine::~SoundEngine()
{}
