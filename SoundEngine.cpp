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

SoundEngine::SoundEngine()
{}

SoundEngine::~SoundEngine()
{}