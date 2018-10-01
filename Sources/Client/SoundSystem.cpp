#include "SoundSystem.h"


SoundSystem::SoundSystem(void)
{
	musicPlaying = false;
	valid = true;
	engine = createIrrKlangDevice();
	if (!engine)
	{
		valid = false;
	}

}

SoundSystem::~SoundSystem(void)
{
	MusicOff();
	engine->drop();
}

bool SoundSystem::isValid()
{
	return valid;
}

void SoundSystem::MusicToggle()
{
	if ( musicPlaying ) 
	{
		MusicOff();
	} else {
		MusicOn();
	}
}

void SoundSystem::MusicOn()
{
	music = engine->play2D("media/music1.ogg", true, false, true);
	music->setVolume( music->getVolume() / 2 );
	// Pause only from sources?
	//music->setIsPaused(false);
	musicPlaying = true;
}

void SoundSystem::MusicOff()
{
	if ( musicPlaying ) 
	{
		music->stop();
		music->drop();
		musicPlaying = false;
	}
}

void SoundSystem::playShot()
{
	engine->play2D("media/shot.wav");
}