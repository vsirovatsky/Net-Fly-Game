#include "StdAfx.h"
#include "PostMainCompDefaultProcessor.h"
#include "Logger.h"
#include "SimpleClientMessage.h"


using namespace simpleclient;

PostMainCompDefaultProcessor::PostMainCompDefaultProcessor(void)
{
}

PostMainCompDefaultProcessor::~PostMainCompDefaultProcessor(void)
{
}

void PostMainCompDefaultProcessor::process( communications::Envelope * en )
{
	if ( en->message->getType() == MESSAGE_TYPE_INNERPING ) {
		PRINT("INNERPING");
	} else {
		PRINT("ANOTHER MESSAGE");
	}
}

PC_MESSAGE_TYPE PostMainCompDefaultProcessor::getType()
{
	return MESSAGE_TYPE_BLANK;
}