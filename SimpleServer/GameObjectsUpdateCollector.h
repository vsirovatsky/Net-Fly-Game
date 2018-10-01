#pragma once

#include "IMessagesSenderProvider.h"
#include "IUserManagementProvider.h"
#include "MovementObjectController.h"
#include <vector>

namespace simpleserver {

class GameObjectsUpdateCollectorsRecord
{
public:
	GameObjectsUpdateCollectorsRecord(){}
	GameObjectsUpdateCollectorsRecord( OBJECT_IDENTITY & _id, SERVER_TIME & _timeCurrent, vector3df & _positionCurrent, vector3df & _positionNext1, vector3df & _positionNext2 ) :
		id(_id), timeCurrent(_timeCurrent ), positionCurrent(_positionCurrent), positionNext1(_positionNext1), positionNext2(_positionNext2) {}
	GameObjectsUpdateCollectorsRecord( const GameObjectsUpdateCollectorsRecord & other ) :
		id(other.id), timeCurrent(other.timeCurrent ), positionCurrent(other.positionCurrent), positionNext1(other.positionNext1), positionNext2(other.positionNext2) {}
	~GameObjectsUpdateCollectorsRecord(){}
	OBJECT_IDENTITY id;
	SERVER_TIME timeCurrent;

	vector3df positionCurrent;
	vector3df positionNext1;
	vector3df positionNext2;
};

class GameObjectsUpdateCollector
{
public:
	GameObjectsUpdateCollector(void);
	~GameObjectsUpdateCollector(void);

	void sendUpdates( IMessagesSenderProvider *, IUserManagementProvider * );

	bool isCollectAll(){return collectAll;}
	void setCollectAll(bool _collectAll){collectAll = _collectAll;}

	void addInformation( OBJECT_IDENTITY & id, MovementState & );
private:
	bool collectAll;

	std::vector<GameObjectsUpdateCollectorsRecord> objects;
};

}