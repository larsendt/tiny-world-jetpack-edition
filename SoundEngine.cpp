#include "SoundEngine.h"

void SoundEngine::Load_Jetpack()
{
	if (!JetpackBuffer.LoadFromFile("sounds/jetpack_noise.wav"))
		{
			// Error...
		}
	JetpackSound.SetBuffer(JetpackBuffer);
	JetpackSound.SetLoop(TRUE);
}

void SoundEngine::Play_Jetpack()
{
	JetpackSound.Play();
}

void SoundEngine::Stop_Jetpack()
{
	JetpackSound.Stop()
}