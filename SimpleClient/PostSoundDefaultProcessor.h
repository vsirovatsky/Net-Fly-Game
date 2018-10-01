#pragma once

#include "PostOffice.h"

namespace simpleclient {

class PostSoundDefaultProcessor : public communications::IPostMessageProcessor
{
public:
	PostSoundDefaultProcessor(void);
	virtual ~PostSoundDefaultProcessor(void);
	virtual void process( communications::Envelope * en );
	virtual PC_MESSAGE_TYPE getType();
};

}