#pragma once

#include "PostOffice.h"
#include "ISimpleSoundManagerPanel.h"

namespace simpleclient {

class PostSoundUserPositionUpdate : public communications::IPostMessageProcessor
{
public:
	PostSoundUserPositionUpdate( ISimpleSoundManagerPanel * );
	virtual ~PostSoundUserPositionUpdate(void);
	virtual void process( communications::Envelope * en );
	virtual PC_MESSAGE_TYPE getType();
private:
	ISimpleSoundManagerPanel * panel;
};

}