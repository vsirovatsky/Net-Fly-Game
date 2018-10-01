#pragma once
#if !defined(__VideoSystem__)
#define __VideoSystem__

#include "include\irrlicht\irrlicht.h"
#include "include\irrlicht\driverChoice.h"
#include "common.h"
#include "User.h"
#include "EnemyPlayer.h"
#include <ClanLib/core.h>


using namespace irr;



class VideoSystem
{
private:
	std::vector<EnemyPlayer> * enemies;
	video::SMaterial material;
	User* user;
	scene::IBillboardSceneNode * bill;
	IrrlichtDevice *device;
	video::IVideoDriver* driver;
	scene::ISceneManager* smgr;
	scene::ITriangleSelector* selector;
	bool valid;
	scene::IMeshSceneNode* q3node;
	CL_Mutex enemyMutex;
public:
	void enemyState( int id, UserState * state );
	User * getUser(){
		return user;
	}
	void run( void );
	bool isValid();
	void setLevel( char * zippedArchive, char * fileName );
	EnemyPlayer * getTargetPlayer( scene::ISceneNode * selectedSceneNode );
	VideoSystem(void);
	~VideoSystem(void);
private:
	video::E_DRIVER_TYPE askForDriverType();
	int getXresolution();
	int getYresolution();
	int getColorDepth();
};

#endif