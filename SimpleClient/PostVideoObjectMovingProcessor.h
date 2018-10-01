#pragma once

#include "PostOffice.h"
#include "ISimpleVideoManagerPanel.h"

namespace simpleclient {

class PostVideoObjectMovingProcessor : public communications::IPostMessageProcessor
{
public:
	PostVideoObjectMovingProcessor( ISimpleVideoManagerPanel * );
	virtual ~PostVideoObjectMovingProcessor(void);
	virtual void process( communications::Envelope * en );
	virtual PC_MESSAGE_TYPE getType();
private:
	ISimpleVideoManagerPanel * panel;
};

}