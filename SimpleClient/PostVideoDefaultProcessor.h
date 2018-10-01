#pragma once

#include "PostOffice.h"

namespace simpleclient {

class PostVideoDefaultProcessor : public communications::IPostMessageProcessor
{
public:
	PostVideoDefaultProcessor(void);
	virtual ~PostVideoDefaultProcessor(void);
	virtual void process( communications::Envelope * en );
	virtual PC_MESSAGE_TYPE getType();
};

}