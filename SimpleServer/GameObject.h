#pragma once

#include "SimpleNetMessages.h"
#include "MovementObjectController.h"
#include "GameObjectsUpdateCollector.h"

namespace simpleserver {

class GameObject
{
public:
	GameObject( OBJECT_IDENTITY );
	virtual ~GameObject(void);

	MovementObjectController movementController;

	void iterate();

	void visit( GameObjectsUpdateCollector & );
private:
	OBJECT_IDENTITY id;
};

}