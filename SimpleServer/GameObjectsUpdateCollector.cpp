#include "StdAfx.h"
#include "GameObjectsUpdateCollector.h"
#include "SimpleNetMessages.h"
#include "Logger.h"

using namespace simpleserver;

GameObjectsUpdateCollector::GameObjectsUpdateCollector(void) : collectAll(false)
{
}


GameObjectsUpdateCollector::~GameObjectsUpdateCollector(void)
{
}

void GameObjectsUpdateCollector::addInformation( OBJECT_IDENTITY & id, MovementState & st )
{
	long t = GetCurrentTime();
	GameObjectsUpdateCollectorsRecord rec = GameObjectsUpdateCollectorsRecord( id, t, st.positionCurrent, st.positionNext1, st.positionNext2 );
	objects.push_back( rec );
}

void GameObjectsUpdateCollector::sendUpdates( IMessagesSenderProvider * senderProvider, IUserManagementProvider * userManagementProvider )
{
	if ( objects.empty() ) 
		return;

	MessageBodyObjectsStatesUpdate * mess = new MessageBodyObjectsStatesUpdate();
	for ( std::vector<GameObjectsUpdateCollectorsRecord>::iterator it = objects.begin(); it != objects.end(); ++it ) {
		mess->objects.push_back( it->id );
		mess->currentTimes.push_back( it->timeCurrent );
		
		mess->currentPositions.push_back( it->positionCurrent.x );
		mess->currentPositions.push_back( it->positionCurrent.y );
		mess->currentPositions.push_back( it->positionCurrent.z );

		mess->nextPositions1.push_back( it->positionNext1.x );
		mess->nextPositions1.push_back( it->positionNext1.y );
		mess->nextPositions1.push_back( it->positionNext1.z );

		mess->nextPositions2.push_back( it->positionNext2.x );
		mess->nextPositions2.push_back( it->positionNext2.y );
		mess->nextPositions2.push_back( it->positionNext2.z );

		std::cout << "sending " << it->id << ", pos: (" << it->positionCurrent.x << ',' << it->positionCurrent.y << ',' << it->positionCurrent.z << ')' << std::endl;
	}
	NetServerMessage messUpdate( SIMPLE_MESSAGE_USER_INFO, NS_TO_ALL_GUID );
	messUpdate.broadcast = true;
	messUpdate.data = mess;
	senderProvider->sendReliable( messUpdate );
	delete messUpdate.data;
}