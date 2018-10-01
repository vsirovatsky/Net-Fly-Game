#include "EnemyPlayer.h"


EnemyPlayer::EnemyPlayer( irr::scene::ISceneManager* smgr, irr::scene::ITriangleSelector* selector, int id )
{
	this->id = id;
	node = smgr->addAnimatedMeshSceneNode(smgr->getMesh("media/ninja.b3d"),
						0, IDFlag_IsPickable | IDFlag_IsHighlightable);
	node->setScale(irr::core::vector3df(10, 10, 10));
	node->setAnimationSpeed(10.f);
	node->getMaterial(0).NormalizeNormals = true;
	// Just do the same as we did above.
	selector = smgr->createTriangleSelector(node);
	node->setTriangleSelector(selector);
	selector->drop();
}

void EnemyPlayer::place( float x, float y, float z, float xDir, float yDir, float zDir )
{
	node->setPosition(irr::core::vector3df(x,y-70,z));
	node->setRotation(irr::core::vector3df(xDir,yDir,zDir));
}

EnemyPlayer::~EnemyPlayer(void)
{

}

int EnemyPlayer::getId()
{
	return id;
}
