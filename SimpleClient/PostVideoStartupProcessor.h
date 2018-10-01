#pragma once

#include "PostOffice.h"
#include "ISimpleVideoManagerPanel.h"

namespace simpleclient {

class PostVideoStartupProcessor : public communications::IPostMessageProcessor
{
public:
	PostVideoStartupProcessor( ISimpleVideoManagerPanel * );
	virtual ~PostVideoStartupProcessor(void);
	virtual void process( communications::Envelope * en );
	virtual PC_MESSAGE_TYPE getType();
private:
	ISimpleVideoManagerPanel * panel;
	void initTerrain();
	void initSky();
	void initLight();
};

}