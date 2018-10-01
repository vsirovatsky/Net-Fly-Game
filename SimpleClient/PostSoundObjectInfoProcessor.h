#pragma once

#include "PostOffice.h"
#include "ISimpleSoundManagerPanel.h"

namespace simpleclient {

class PostSoundObjectInfoProcessor : public communications::IPostMessageProcessor
{
public:
	PostSoundObjectInfoProcessor( ISimpleSoundManagerPanel * );
	virtual ~PostSoundObjectInfoProcessor(void);
	virtual void process( communications::Envelope * en );
	virtual PC_MESSAGE_TYPE getType();
private:
	ISimpleSoundManagerPanel * panel;
};

}