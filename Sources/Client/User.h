#pragma once
#if !defined(__User__)
#define __User__

#include "include\irrlicht\irrlicht.h"
#include "include\irrlicht\driverChoice.h"
#include "common.h"
#include "SoundSystem.h"
#include "EnemyPlayer.h"
#include <ClanLib/core.h>

using namespace irr;

class UserState 
{
public:
	float x;
	float y;
	float z;
	float xDir;
	float yDir;
	float zDir;
};


class MyEventReceiver : public IEventReceiver
{
public:
	// This is the one method that we have to implement
	virtual bool OnEvent(const SEvent& event)
	{
		// Remember whether each key is down or up
		if (event.EventType == irr::EET_KEY_INPUT_EVENT)
			KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
		if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
		{
			mouseClick = event.MouseInput.isLeftPressed();
		}

		return false;
	}

	// This is used to check whether a key is being held down
	virtual bool IsKeyDownNotClear(EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}

	virtual bool IsKeyDown( EKEY_CODE keyCode )
	{
		bool result = KeyIsDown[keyCode];
		KeyIsDown[keyCode] = false;
		return result;
	}
	
	MyEventReceiver()
	{
		for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	}

	bool isMouseClicked()
	{
		if ( mouseClick )
		{
			mouseClick = false;
			return true;
		} else 
			return false;
	}

private:
	// We use this array to store the current state of each key
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
	bool mouseClick;
};

class User
{
private:
	int health;
	clientListener * cListener;
	SoundSystem * sound;
	u32 then;
	MyEventReceiver * receiver;
	scene::ISceneManager* smgr;
	scene::ICameraSceneNode* camera;
	scene::ITriangleSelector* selector;
	//scene::IAnimatedMeshSceneNode* character;
	scene::IMeshSceneNode* character;
	CL_Mutex stateMutex;
public:
	User();
	~User(void);
	void setClientListener( clientListener * cListener )
	{
		this->cListener = cListener;
	}
	void populateState( UserState * state );
	void acceptState( UserState * state );
	void init( scene::ISceneManager* smgr );
	void addToSelector( scene::IMeshSceneNode* node );
	scene::ICameraSceneNode* getCamera();
	void iterate( IrrlichtDevice *device );
	void iterate( IrrlichtDevice *device, EnemyPlayer * p );
	MyEventReceiver * getReceiver();
	void meHitted( int amount );
private:
	void createMyPerson();
};

#endif

