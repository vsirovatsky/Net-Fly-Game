#pragma once

#include <vector>
#include <hash_map>
#include "SimpleServerTypeDefs.h"
#include "SimpleNetMessages.h"
#include "netSystemTypeDefs.h"
#include "GameObject.h"

namespace simpleserver {

class GameObjectsRegister
{
public:
	GameObjectsRegister(void);
	virtual ~GameObjectsRegister(void);

	virtual bool isObjectExists( OBJECT_IDENTITY );
	virtual void addObject( OBJECT_IDENTITY, GameObject * );
	virtual void removeObject( OBJECT_IDENTITY );
	virtual GameObject * getObject( OBJECT_IDENTITY );

	virtual void iterateAll();
	virtual void visitAll( GameObjectsUpdateCollector & );
private:
	std::hash_map<OBJECT_IDENTITY, GameObject *> objects;
};

}