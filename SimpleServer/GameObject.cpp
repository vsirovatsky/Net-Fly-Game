#include "StdAfx.h"
#include "GameObject.h"

using namespace simpleserver;

GameObject::GameObject( OBJECT_IDENTITY _id ) : id(_id)
{
}


GameObject::~GameObject(void)
{
}

void GameObject::iterate()
{
	movementController.iterate();
}

void GameObject::visit( GameObjectsUpdateCollector & visitor )
{
	if ( visitor.isCollectAll() || movementController.isDirty() ) {
		visitor.addInformation( id, movementController.getState() );
		movementController.setDirty( false );
	}
}