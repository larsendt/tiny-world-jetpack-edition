



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


void SoundEngine::Load_Asplode()
{
	if (!AsplodeBuffer.LoadFromFile("sounds/asplode.wav"))
		{
		
		}
	AsplodeSound.SetBuffer(AsplodeBuffer);
	AsplodeSound.SetLoop(false);
	AsplodeSound.SetVolume(40);
}

void SoundEngine::Play_Asplode()
{
	

		AsplodeSound.Play();

}


void SoundEngine::Load_WinMusic()
{
	if (!Music1.OpenFromFile("sounds/win.ogg"))
		{
			// Error...
		}
	Music1.SetLoop(true);
}
void SoundEngine::Play_WinMusic()
{
	Music1.Play();
}
void SoundEngine::Pause_WinMusic()
{
	Music1.Pause();
}
void SoundEngine::Kill_WinMusic()
{
	Music1.Stop();
}


void SoundEngine::Load_AmbientMusic()
{
	if (!Music2.OpenFromFile("sounds/ambient.ogg"))
		{
			// Error...
		}
	Music2.SetLoop(true);
}
void SoundEngine::Play_AmbientMusic()
{
	Music2.Play();
}
void SoundEngine::Pause_AmbientMusic()
{
	Music2.Pause();
}
void SoundEngine::Kill_AmbientMusic()
{
	Music2.Stop();
}


SoundEngine::SoundEngine()
{}

SoundEngine::~SoundEngine()
{}


