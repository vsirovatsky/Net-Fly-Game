#include "StdAfx.h"
#include "PostMainCompSoundResourceResolveProcessor.h"
#include "Logger.h"
#include "SimpleClientMessage.h"
#include "SimpleSoundMessage.h"

using namespace simpleclient;

PostMainCompSoundResourceResolveProcessor::PostMainCompSoundResourceResolveProcessor( ISimpleMainComponentPanel * _panel ) : panel(_panel)
{
}

PostMainCompSoundResourceResolveProcessor::~PostMainCompSoundResourceResolveProcessor(void)
{
}

void PostMainCompSoundResourceResolveProcessor::process( communications::Envelope * en )
{
	InnerSoundResourceResolveRequest * resReq = (InnerSoundResourceResolveRequest *)(en->message);
	InnerSoundResourceResolveResponce * resRes = new InnerSoundResourceResolveResponce();
	resRes->body = resReq->body;
	resRes->resource = panel->getFileSystem()->getValueInResource( resReq->body->resourceId, resReq->body->soundId );
	panel->getPostOffice()->send( resRes, communications::SOUND_COMPONENT_ID );
}

PC_MESSAGE_TYPE PostMainCompSoundResourceResolveProcessor::getType()
{
	return MESSAGE_TYPE_SOUND_RESOURCE_RESOLVE;
}