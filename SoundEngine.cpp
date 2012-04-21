#include "SoundEngine.h"

void SoundEngine::Load_Jetpack()
{
	if (!JetpackBuffer.LoadFromFile("sounds/jetpack_noise.wav"))
		{
			
		}
	JetpackSound.SetBuffer(JetpackBuffer);
	JetpackSound.SetLoop(true);
}

void SoundEngine::Play_Jetpack(bool is_playing)
{
	JetStatus = JetpackSound.GetStatus();
	if (is_playing)
		{
		if (JetStatus != 2)
			{
				JetpackSound.Play();
			}
		}

	else JetpackSound.Stop();
}

void SoundEngine::Load_Music()
{
	if (!Music1.OpenFromFile("sounds/music.ogg"))
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
