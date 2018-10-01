#pragma once

#include "ISimpleVideoManagerPanel.h"
#include "ThreadWrapper.h"
#include "SimpleControlManager.h"
#include <hash_map>

namespace simpleclient {

class SimpleVideoManager : public common::thread, public ISimpleVideoManagerPanel, public communications::IPostFilter, public ISimpleMovementListener
{
public:
	SimpleVideoManager( SimpleVideoManagerContext * nContext );
	~SimpleVideoManager(void);

	//from IPostFilter
	virtual bool pass( communications::Envelope * en );

	virtual void run();

	//from ISimpleVideoManagerPanel
	virtual ISimpleVideoState * getState(){return videoState;};
	virtual VideoObjectsRegister & getObjectsRegister(){return *objectsRegister;};
	virtual videosystem::VideoSystemFacade * getVideoSystem(){return sysVideo;};
	virtual videosystem::IVideoCamera * getCamera(){return camera;};
	virtual SimpleVideoManagerContext * getContext(){return context;};
	virtual void send( communications::IMessage * mess, communications::COMPONENT_IDS receiverId );
	virtual void initialize();
	virtual VideoObjectMovementController * getCameraMovementController(){return cameraMovementController;}
	virtual VideoSoundPlayRequester * getVideoSoundPlayRequester(){return videoSoundPlayRequester;}

	//from ISimpleMovementListener
	virtual void notifyMovementPressed();
	virtual void notifyMovementReleased();
private:
	ISimpleVideoState * videoState;
	videosystem::VideoSystemFacade * sysVideo;
	videosystem::IVideoCamera * camera;
	SimpleVideoManagerContext * context;
	communications::AbstractPostOffice * postOffice;
	VideoObjectsRegister * objectsRegister;
	VideoObjectMovementController * cameraMovementController;
	VideoSoundPlayRequester * videoSoundPlayRequester;

	void runImpl();
	void updateObjectsLocations();

	long prevSendingPositionTime;

	SimpleControlManager * controlMan;
};

}