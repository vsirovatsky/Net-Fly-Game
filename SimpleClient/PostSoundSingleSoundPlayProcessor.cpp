#include "StdAfx.h"
#include "PostSoundSingleSoundPlayProcessor.h"
#include "Logger.h"
#include "SimpleClientMessage.h"
#include "SimpleSoundMessage.h"


using namespace simpleclient;

PostSoundSingleSoundPlayProcessor::PostSoundSingleSoundPlayProcessor( ISimpleSoundManagerPanel * _panel ) : panel(_panel)
{
}

PostSoundSingleSoundPlayProcessor::~PostSoundSingleSoundPlayProcessor(void)
{
}

void PostSoundSingleSoundPlayProcessor::process( communications::Envelope * en )
{
	InnerSoundSinglePlay * soundPlay = (InnerSoundSinglePlay *)(en->message);
	if ( (soundPlay->resourceId.empty()) || (soundPlay->soundId.empty()) ) {
		PRINTDEBUG("NO sound information in MESSAGE_TYPE_SOUND_SINGLE_PLAY message", en);
		return;
	}
	COMMON_STRING * soundAddress = panel->getResolvedResourcesContainer()->getAddress( soundPlay->resourceId, soundPlay->soundId );
	if ( soundAddress == 0 ) {
		InnerSoundResourceResolveRequest * resReq = new InnerSoundResourceResolveRequest();
		resReq->body = soundPlay;
		en->deleteMessage = false;
		panel->getPostOffice()->send( resReq, communications::MASTER_COMPONENT_ID );
	} else {
		soundsystem::SoundData3D sd = soundsystem::SoundData3D();
		sd.address = *soundAddress;
		sd.looped = false;
		sd.maxDis = 1000;
		sd.minDis = 0;
		sd.volume = panel->getState()->getSoundVolume();
		sd.track = false;
		sd.x = soundPlay->x;
		sd.y = soundPlay->y;
		sd.z = soundPlay->z;
		panel->getSysSound()->play3D( sd );
	}
}

PC_MESSAGE_TYPE PostSoundSingleSoundPlayProcessor::getType()
{
	return MESSAGE_TYPE_SOUND_SINGLE_PLAY;
}