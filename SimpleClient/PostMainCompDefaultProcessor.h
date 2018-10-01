#pragma once

#include "PostOffice.h"

namespace simpleclient {

class PostMainCompDefaultProcessor : public communications::IPostMessageProcessor
{
public:
	PostMainCompDefaultProcessor(void);
	virtual ~PostMainCompDefaultProcessor(void);
	virtual void process( communications::Envelope * en );
	virtual PC_MESSAGE_TYPE getType();
};

}