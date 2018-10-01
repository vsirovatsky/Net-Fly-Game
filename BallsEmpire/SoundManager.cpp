#include "SoundManager.h"

void SoundManager::playDefault()
{
	SYSTEMCORE->Effect_PlayEx( SYSTEM->getEffect("mediab/menu.wav") ,100 );
}