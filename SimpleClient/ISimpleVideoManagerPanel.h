#pragma once

#include "SimpleVideoState.h"
#include "VideoObjectsRegister.h"
#include "VideoSystemFacade.h"
#include "VideoSystemTypeDefs.h"
#include "CommunicationsFacade.h"
#include "SimpleClientMessage.h"
#include "SimpleClientContext.h"
#include "SimpleNetMessages.h"
#include "VideoObjectMovementController.h"
#include "VideoSoundPlayRequester.h"

namespace simpleclient {

class ISimpleVideoManagerPanel {
public:
	virtual ISimpleVideoState * getState() = 0;
	virtual VideoObjectsRegister & getObjectsRegister() = 0;
	virtual videosystem::VideoSystemFacade * getVideoSystem() = 0;
	virtual void send( communications::IMessage * mess, communications::COMPONENT_IDS receiverId ) = 0;
	virtual videosystem::IVideoCamera * getCamera() = 0;
	virtual VideoObjectMovementController * getCameraMovementController() = 0;
	virtual SimpleVideoManagerContext * getContext() = 0;
	virtual VideoSoundPlayRequester * getVideoSoundPlayRequester() = 0;
	virtual void initialize() = 0;
};

}