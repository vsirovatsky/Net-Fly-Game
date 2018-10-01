#include "StdAfx.h"
#include "PostSoundObjectInfoProcessor.h"
#include "Logger.h"
#include "SimpleClientMessage.h"
#include "SimpleSoundMessage.h"


using namespace simpleclient;

PostSoundObjectInfoProcessor::PostSoundObjectInfoProcessor( ISimpleSoundManagerPanel * _panel ) : panel(_panel)
{
}

PostSoundObjectInfoProcessor::~PostSoundObjectInfoProcessor(void)
{
}

void PostSoundObjectInfoProcessor::process( communications::Envelope * en )
{
	InnerSoundObjectInfo * soundPlay = (InnerSoundObjectInfo *)(en->message);
	if ( soundPlay->info.isWithSound() ) {
		if ( (soundPlay->resourceId.empty()) || (soundPlay->soundId.empty()) ) {
			PRINTDEBUG("NO sound information in MESSAGE_TYPE_SOUND_OBJECT_INFO message", en);
			return;
		}
		COMMON_STRING * soundAddress = panel->getResolvedResourcesContainer()->getAddress( soundPlay->resourceId, soundPlay->soundId );
		if ( soundAddress == 0 ) {
			InnerSoundResourceResolveRequest * resReq = new InnerSoundResourceResolveRequest();
			resReq->body = soundPlay;
			en->deleteMessage = false;
			panel->getPostOffice()->send( resReq, communications::MASTER_COMPONENT_ID );
			return;
		}
	}
	panel->getGameObjectSoundViewsRegister()->processSoundData( soundPlay->info );
	/*
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
	*/
}

PC_MESSAGE_TYPE PostSoundObjectInfoProcessor::getType()
{
	return MESSAGE_TYPE_SOUND_OBJECT_INFO;
}