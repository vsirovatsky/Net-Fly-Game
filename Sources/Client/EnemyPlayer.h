#pragma once
#if !defined(__EnemyPlayer__)
#define __EnemyPlayer__

#include "include\irrlicht\irrlicht.h"
#include "common.h"

class EnemyPlayer
{
public:
	EnemyPlayer( irr::scene::ISceneManager* smgr, irr::scene::ITriangleSelector* selector, int id );
	~EnemyPlayer(void);
	void place( float x, float y, float z, float xDir, float yDir, float zDir );
	int getId();
	irr::scene::ISceneNode * getNode()
	{
		return node;
	}
private:
	int id;
	irr::scene::IAnimatedMeshSceneNode* node;
};

#endif