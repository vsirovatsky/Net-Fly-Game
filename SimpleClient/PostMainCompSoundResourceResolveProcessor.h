#pragma once

#include "PostOffice.h"
#include "ISimpleMainComponentPanel.h"

namespace simpleclient {

class PostMainCompSoundResourceResolveProcessor : public communications::IPostMessageProcessor
{
public:
	PostMainCompSoundResourceResolveProcessor( ISimpleMainComponentPanel * );
	virtual ~PostMainCompSoundResourceResolveProcessor(void);
	virtual void process( communications::Envelope * en );
	virtual PC_MESSAGE_TYPE getType();
private:
	ISimpleMainComponentPanel * panel;
};

}