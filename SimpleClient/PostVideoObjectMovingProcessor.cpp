#include "StdAfx.h"
#include "PostVideoObjectMovingProcessor.h"
#include "Logger.h"
#include "SimpleClientMessage.h"
#include "VideoSystemTypeDefs.h"
#include <sstream>

using namespace simpleclient;

PostVideoObjectMovingProcessor::PostVideoObjectMovingProcessor( ISimpleVideoManagerPanel * _panel ) : panel(_panel)
{
}

PostVideoObjectMovingProcessor::~PostVideoObjectMovingProcessor(void)
{
}

void PostVideoObjectMovingProcessor::process( communications::Envelope * en )
{
	InnerObjectLocationMessage * locationMess = (InnerObjectLocationMessage *)(en->message);
	int counter = 0;
	//for( std::vector<OBJECT_IDENTITY>::iterator it = locationMess->objects.begin(); it != locationMess->objects.end(); ++it ){
	for ( int i = 0; i < locationMess->objects.size(); ++i ) {
		long id = locationMess->objects[i];
		counter = 3*i;
		if (panel->getState()->getIdentity() == id) {
			VideoObjectMovementController * contr = panel->getCameraMovementController();
			contr->setCurrentTimeFromServer( locationMess->currentTimes[i] );
			contr->setCurrentPosition( locationMess->currentPositions[counter], locationMess->currentPositions[counter+1], locationMess->currentPositions[counter+2] );
			contr->setNextPosition1( locationMess->nextPositions1[counter], locationMess->nextPositions1[counter+1], locationMess->nextPositions1[counter+2] );
			contr->setNextPosition2( locationMess->nextPositions2[counter], locationMess->nextPositions2[counter+1], locationMess->nextPositions2[counter+2] );
			contr->checkReceivedInfo();
			//std::stringstream ss;
			//ss << "MY POS: " << id << '(' << locationMess->currentPositions[counter] << ',' << locationMess->currentPositions[counter+1] << ',' << locationMess->currentPositions[counter+2] << ')';
			//panel->getVideoSystem()->get2DControlPanel()->printText(12, ss.str());
			//videosystem::vector3df pos = videosystem::vector3df(locationMess->currentPositions[counter], locationMess->currentPositions[counter+1], locationMess->currentPositions[counter+2]);
			//panel->getCamera()->setPosition( pos );
			//std::stringstream ss;
			//ss << "( " << pos.x << " , " << pos.y << " , " << pos.z << " )";
			//panel->getVideoSystem()->get2DControlPanel()->printText(1, ss.str());
		} else {
			videosystem::IVideoObject * obj = panel->getObjectsRegister().get( id );
			if ( obj == 0 ) {
				videosystem::VideoSimpleObjectCreateData data = videosystem::VideoSimpleObjectCreateData();
				data.id = id;
				data.isTextured = true;
				data.polynum = 32;
				data.radius = 50.0f;
				data.type =  videosystem::VS_SIMPLE_OBJECT_TYPE_SPHERE;
				data.textureFile = VS_STRING( "media/wall.bmp" );
				obj = panel->getVideoSystem()->createVideoSimpleObject( data );
				obj->setPosition( videosystem::vector3df(locationMess->currentPositions[counter], locationMess->currentPositions[counter+1], locationMess->currentPositions[counter+2]) );
				panel->getObjectsRegister().store( id, obj );
			}
			VideoObjectMovementController * contr = panel->getObjectsRegister().getMovementController( id );
			contr->setCurrentTimeFromServer( locationMess->currentTimes[i] );
			contr->setCurrentPosition( locationMess->currentPositions[counter], locationMess->currentPositions[counter+1], locationMess->currentPositions[counter+2] );
			contr->setNextPosition1( locationMess->nextPositions1[counter], locationMess->nextPositions1[counter+1], locationMess->nextPositions1[counter+2] );
			contr->setNextPosition2( locationMess->nextPositions2[counter], locationMess->nextPositions2[counter+1], locationMess->nextPositions2[counter+2] );
			contr->checkReceivedInfo();
			//obj->setPosition( videosystem::vector3df(locationMess->currentPositions[counter], locationMess->currentPositions[counter+1], locationMess->currentPositions[counter+2]) );
			std::stringstream ss;
			ss << "OBJECT: " << id << '(' << locationMess->currentPositions[counter] << ',' << locationMess->currentPositions[counter+1] << ',' << locationMess->currentPositions[counter+2] << ')';
			panel->getVideoSystem()->get2DControlPanel()->printText(11, ss.str());
		}
	}

}

PC_MESSAGE_TYPE PostVideoObjectMovingProcessor::getType()
{
	return MESSAGE_TYPE_OBJECT_LOCATION;
}