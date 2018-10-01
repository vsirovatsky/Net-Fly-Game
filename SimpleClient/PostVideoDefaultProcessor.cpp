#include "StdAfx.h"
#include "PostVideoDefaultProcessor.h"
#include "Logger.h"
#include "SimpleClientMessage.h"

using namespace simpleclient;

PostVideoDefaultProcessor::PostVideoDefaultProcessor(void)
{
}

PostVideoDefaultProcessor::~PostVideoDefaultProcessor(void)
{
}

void PostVideoDefaultProcessor::process( communications::Envelope * en )
{
	if ( en->message->getType() == MESSAGE_TYPE_INNERPING ) {
		PRINTDEBUG("PostVideoDefaultProcessor: ", en);
	} else {
		PRINTDEBUG("PostVideoDefaultProcessor: ", en);
	}
}

PC_MESSAGE_TYPE PostVideoDefaultProcessor::getType()
{
	return MESSAGE_TYPE_BLANK;
}