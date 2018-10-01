#include "StdAfx.h"
#include "SoundSystemFacade.h"

namespace soundsystem {

SoundSystemFacade * SoundSystemFacade::pInstance = 0;

SoundSystemFacade * SoundSystemFacade::INSTANCE(){
	if ( pInstance == 0 ) {
		pInstance = new SoundSystemFacade();
	}
	return pInstance;
}

SoundSystemFacade::SoundSystemFacade(void)
{
	manager = SoundSystemFactory::createSoundSystemManager();
}


SoundSystemFacade::~SoundSystemFacade(void)
{
	delete manager;
}

	void SoundSystemFacade::stopAllSound()
	{
		manager->stopAllSound();
	}
	void SoundSystemFacade::init()
	{
		manager->init();
	}

	void SoundSystemFacade::play2D( SoundData data )
	{
		manager->play2D( data );
	}

	void SoundSystemFacade::play3D( SoundData3D data )
	{
		manager->play3D( data );
	}

	void SoundSystemFacade::drop( SS_ID id )
	{
		manager->drop( id );
	}

	void SoundSystemFacade::update3DPosition( SS_ID id, float x, float y, float z )
	{
		manager->update3DPosition( id, x, y, z );
	}

	void SoundSystemFacade::update3DMinDistance( SS_ID id, float dis )
	{
		manager->update3DMinDistance( id, dis );
	}

	void SoundSystemFacade::update3DMaxDistance( SS_ID id, float dis )
	{
		manager->update3DMaxDistance( id, dis );
	}

	void SoundSystemFacade::updateVolume( SS_ID id, float volume )
	{
		manager->updateVolume( id, volume );
	}

}