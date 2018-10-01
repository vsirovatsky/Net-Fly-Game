#pragma once

#include <hash_map>
#include "SimpleClientTypeDefs.h"
#include "SimpleNetMessages.h"
#include "SoundSystemFacade.h"
#include "SoundSystemFacade.h"
#include "SimpleSoundMessage.h"
#include "SimpleSoundResolvedResourcesContainer.h"

namespace simpleclient {

class One3DSound {
public:
	One3DSound() : dirty(false), startSound(false), stopSound(false), playing(false) {}
	bool dirty;
	SS_ID id;
	SS_STRING resourceId;
	SS_STRING soundId;
	bool startSound;
	bool stopSound;
	bool playing;
};

class GameObjectSoundView
{
public:
	GameObjectSoundView(OBJECT_IDENTITY, soundsystem::SoundSystemFacade *, vector3df *, SimpleSoundResolvedResourcesContainer * );
	~GameObjectSoundView(void);

	void iterate();
	void processSoundData( SoundInformation & );
private:
	float x;
	float y;
	float z;
	bool dirty;
	OBJECT_IDENTITY id;
	soundsystem::SoundSystemFacade * sysSound;
	SimpleSoundResolvedResourcesContainer * resourcesContainer;
	vector3df * currentUserPos;
	std::hash_map<SS_ID, One3DSound> sounds;

	void iterateForOne( One3DSound & );
};

}