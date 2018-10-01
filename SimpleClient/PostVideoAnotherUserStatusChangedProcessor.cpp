#include "StdAfx.h"
#include "PostVideoAnotherUserStatusChangedProcessor.h"
#include <sstream>

using namespace simpleclient;

PostVideoAnotherUserStatusChangedProcessor::PostVideoAnotherUserStatusChangedProcessor( ISimpleVideoManagerPanel * _panel ) : panel(_panel)
{
}


PostVideoAnotherUserStatusChangedProcessor::~PostVideoAnotherUserStatusChangedProcessor(void)
{
}

void PostVideoAnotherUserStatusChangedProcessor::process( communications::Envelope * en )
{
	PRINTDEBUG("PostVideoAnotherUserStatusChangedProcessor received: ", en);
	InnerObjectAnotherUserStatusChanged * mess = (InnerObjectAnotherUserStatusChanged *)(en->message);

	std::stringstream ss;
	if ( mess->userConnceted ) {
		ss << "USER CONNECTED: ";
	} else {
		ss << "USER DISCONNECTED: ";
		panel->getObjectsRegister().remove( mess->userId );
	}
	ss << mess->userId;

	panel->getVideoSystem()->get2DControlPanel()->printText(5, ss.str() );
}

PC_MESSAGE_TYPE PostVideoAnotherUserStatusChangedProcessor::getType()
{
	return MESSAGE_TYPE_ANOTHER_USER_STATUS_CHANGED;
}