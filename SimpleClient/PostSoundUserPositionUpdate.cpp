#include "StdAfx.h"
#include "PostSoundUserPositionUpdate.h"
#include "Logger.h"
#include "SimpleClientMessage.h"
#include "SimpleSoundMessage.h"


using namespace simpleclient;

PostSoundUserPositionUpdate::PostSoundUserPositionUpdate( ISimpleSoundManagerPanel * _panel ) : panel(_panel)
{
}

PostSoundUserPositionUpdate::~PostSoundUserPositionUpdate(void)
{
}

void PostSoundUserPositionUpdate::process( communications::Envelope * en )
{
	InnerSoundUserPosition * userPos = (InnerSoundUserPosition *)(en->message);
	panel->getGameObjectSoundViewsRegister()->setCurrentPos( userPos->pos );
}

PC_MESSAGE_TYPE PostSoundUserPositionUpdate::getType()
{
	return MESSAGE_TYPE_SOUND_USER_POSITION;
}