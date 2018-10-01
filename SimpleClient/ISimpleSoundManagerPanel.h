#pragma once

#include "CommunicationsFacade.h"
#include "SimpleClientMessage.h"
#include "SoundSystemFacade.h"
#include "SimpleSoundResolvedResourcesContainer.h"
#include "SimpleSoundState.h"
#include "SimpleClientContext.h"
#include "GameObjectSoundViewsRegister.h"

namespace simpleclient {

class ISimpleSoundManagerPanel {
public:
	ISimpleSoundManagerPanel(){};
	virtual ~ISimpleSoundManagerPanel(){};
	virtual SimpleSoundManagerContext * getContext() = 0;
	virtual ISimpleSoundState * getState() = 0;
	virtual soundsystem::SoundSystemFacade * getSysSound() = 0;
	virtual communications::AbstractPostOffice * getPostOffice() = 0;
	virtual SimpleSoundResolvedResourcesContainer * getResolvedResourcesContainer() = 0;
	virtual GameObjectSoundViewsRegister * getGameObjectSoundViewsRegister() = 0;
};

}