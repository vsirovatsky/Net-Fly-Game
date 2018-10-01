#pragma once

#include "PostOffice.h"

namespace simpleclient {

class PostNetDefaultProcessor : public communications::IPostMessageProcessor
{
public:
	PostNetDefaultProcessor(void);
	virtual ~PostNetDefaultProcessor(void);
	virtual void process( communications::Envelope * en );
	virtual PC_MESSAGE_TYPE getType();
};

}