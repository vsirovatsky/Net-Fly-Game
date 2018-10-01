#include "StdAfx.h"
#include "PostSoundDefaultProcessor.h"
#include "Logger.h"
#include "SimpleClientMessage.h"


using namespace simpleclient;

PostSoundDefaultProcessor::PostSoundDefaultProcessor(void)
{
}

PostSoundDefaultProcessor::~PostSoundDefaultProcessor(void)
{
}

void PostSoundDefaultProcessor::process( communications::Envelope * en )
{
	if ( en->message->getType() == MESSAGE_TYPE_INNERPING ) {
		PRINT("INNERPING");
	} else {
		PRINT("ANOTHER MESSAGE");
	}
}

PC_MESSAGE_TYPE PostSoundDefaultProcessor::getType()
{
	return MESSAGE_TYPE_BLANK;
}