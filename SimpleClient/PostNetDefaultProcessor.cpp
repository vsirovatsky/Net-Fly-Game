#include "StdAfx.h"
#include "PostNetDefaultProcessor.h"
#include "Logger.h"
#include "SimpleClientMessage.h"

using namespace simpleclient;

PostNetDefaultProcessor::PostNetDefaultProcessor(void)
{
}


PostNetDefaultProcessor::~PostNetDefaultProcessor(void)
{
}

void PostNetDefaultProcessor::process( communications::Envelope * en )
{
	if ( en->message->getType() == MESSAGE_TYPE_INNERPING ) {
		PRINT("INNERPING");
	} else {
		PRINT("ANOTHER MESSAGE");
	}
}

PC_MESSAGE_TYPE PostNetDefaultProcessor::getType()
{
	return MESSAGE_TYPE_BLANK;
}