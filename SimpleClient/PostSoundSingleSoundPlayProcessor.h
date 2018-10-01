#pragma once

#include "PostOffice.h"
#include "ISimpleSoundManagerPanel.h"

namespace simpleclient {

class PostSoundSingleSoundPlayProcessor : public communications::IPostMessageProcessor
{
public:
	PostSoundSingleSoundPlayProcessor( ISimpleSoundManagerPanel * );
	virtual ~PostSoundSingleSoundPlayProcessor(void);
	virtual void process( communications::Envelope * en );
	virtual PC_MESSAGE_TYPE getType();
private:
	ISimpleSoundManagerPanel * panel;
};

}