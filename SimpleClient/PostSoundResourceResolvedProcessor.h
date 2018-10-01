#pragma once

#include "PostOffice.h"
#include "ISimpleSoundManagerPanel.h"

namespace simpleclient {

class PostSoundResourceResolvedProcessor : public communications::IPostMessageProcessor
{
public:
	PostSoundResourceResolvedProcessor( ISimpleSoundManagerPanel * );
	virtual ~PostSoundResourceResolvedProcessor(void);
	virtual void process( communications::Envelope * en );
	virtual PC_MESSAGE_TYPE getType();
private:
	ISimpleSoundManagerPanel * panel;
};

}