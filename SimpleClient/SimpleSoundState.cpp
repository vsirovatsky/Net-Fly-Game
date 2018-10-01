#include "StdAfx.h"
#include "SimpleSoundState.h"

using namespace simpleclient;

SimpleSoundState::SimpleSoundState(void)
{
}


SimpleSoundState::~SimpleSoundState(void)
{
}

SIMPLE_FLOAT & SimpleSoundState::getSoundVolume()
{
	return soundVolume;
}

SIMPLE_FLOAT & SimpleSoundState::getMusicVolume()
{
	return musicVolume;
}

void SimpleSoundState::setSoundVolume( SIMPLE_FLOAT & _soundVolume )
{
	soundVolume = _soundVolume;
}

void SimpleSoundState::setMusicVolume( SIMPLE_FLOAT & _musicVolume )
{
	musicVolume = _musicVolume;
}
