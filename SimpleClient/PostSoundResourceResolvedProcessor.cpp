#include "StdAfx.h"
#include "PostSoundResourceResolvedProcessor.h"
#include "Logger.h"
#include "SimpleClientMessage.h"
#include "SimpleSoundMessage.h"


using namespace simpleclient;

PostSoundResourceResolvedProcessor::PostSoundResourceResolvedProcessor( ISimpleSoundManagerPanel * _panel ) : panel(_panel)
{
}

PostSoundResourceResolvedProcessor::~PostSoundResourceResolvedProcessor(void)
{
}

void PostSoundResourceResolvedProcessor::process( communications::Envelope * en )
{
	InnerSoundResourceResolveResponce * resRes = (InnerSoundResourceResolveResponce *)(en->message);
	panel->getResolvedResourcesContainer()->addAddress(  resRes->body->resourceId, resRes->body->soundId, resRes->resource );
	panel->getPostOffice()->send( resRes->body, communications::SOUND_COMPONENT_ID );
}

PC_MESSAGE_TYPE PostSoundResourceResolvedProcessor::getType()
{
	return MESSAGE_TYPE_SOUND_RESOURCE_RESPONCE;
}