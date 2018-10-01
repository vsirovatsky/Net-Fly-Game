#pragma once

#include "PostOffice.h"
#include "ISimpleVideoManagerPanel.h"

namespace simpleclient {

class PostVideoAnotherUserStatusChangedProcessor : public communications::IPostMessageProcessor
{
public:
	PostVideoAnotherUserStatusChangedProcessor( ISimpleVideoManagerPanel * );
	virtual ~PostVideoAnotherUserStatusChangedProcessor(void);
	virtual void process( communications::Envelope * en );
	virtual PC_MESSAGE_TYPE getType();
private:
	ISimpleVideoManagerPanel * panel;
	void initTerrain();
	void initSky();
	void initLight();
};

}