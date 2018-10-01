#pragma once

#include "VideoSystemException.h"
#include "VideoSystemTypeDefs.h"

#include <irrlicht.h>

using namespace irr;

namespace videosystem {

class VideoObjectIrrlicht : public IVideoObject
{
public:
	VideoObjectIrrlicht(VS_VIDEO_OBJECT_ID id, scene::ISceneManager* nsmgr, irr::video::IVideoDriver * ndriver) : IVideoObject(id){ smgr = nsmgr; driver = ndriver; node = 0; }
	virtual ~VideoObjectIrrlicht(void);
	void create( VideoObjectCreateData data );
public:
	virtual void setPosition( vector3df & pos );
	virtual void setRotation( vector3df & rot );
	virtual void setScale( vector3df & scl );
	virtual vector3df getPosition();
	virtual vector3df getRotation();
	virtual vector3df getScale();

	virtual void remove();
	scene::IMeshSceneNode * getNode() {return node;}
protected:
	scene::ISceneManager * smgr;
	irr::video::IVideoDriver * driver;
	scene::IMeshSceneNode * node;
};

class VideoAnimatedObjectIrrlicht : public IVideoAnimatedObject
{
public:
public:
	VideoAnimatedObjectIrrlicht(VS_VIDEO_OBJECT_ID id, scene::ISceneManager* nsmgr, irr::video::IVideoDriver * ndriver) : IVideoAnimatedObject(id){ smgr = nsmgr; driver = ndriver; node = 0; }
	virtual ~VideoAnimatedObjectIrrlicht(void);
	void create( VideoObjectCreateData data );
public:
	virtual void setPosition( vector3df & pos );
	virtual void setRotation( vector3df & rot );
	virtual void setScale( vector3df & scl );
	virtual vector3df getPosition();
	virtual vector3df getRotation();
	virtual vector3df getScale();

	virtual void remove();

	virtual void setAnimationSpead( VS_ANIMATION_SPEAD spead );
	virtual void setAnimationPosition( VS_ANIMATION_POSITION begin, VS_ANIMATION_POSITION end );
	virtual void startAnimation();
	virtual void stopAnimation();
protected:
	scene::ISceneManager * smgr;
	irr::video::IVideoDriver * driver;
	scene::IAnimatedMeshSceneNode * node;
};

class VideoCameraIrrlicht : public IVideoCamera
{
public:
	VideoCameraIrrlicht( scene::ISceneManager * nsmgr ) : IVideoCamera() { smgr = nsmgr; }
	virtual ~VideoCameraIrrlicht(){}
	void create();
	virtual void setPosition( vector3df & pos );
	virtual void setTarget( vector3df & pos );
	virtual vector3df getRotaition();
	virtual vector3df getPosition();
	scene::ICameraSceneNode * getCameraNode(){return camera;}
private:
	scene::ISceneManager * smgr;
	scene::ICameraSceneNode * camera;
};

class VideoLightIrrlicht : public ILight 
{
public:
	VideoLightIrrlicht( scene::ISceneManager * nsmgr ) : ILight() { smgr = nsmgr; }
	virtual ~VideoLightIrrlicht();
	void create();
	virtual void setPosition( vector3df & pos );
	virtual void setColor( color4d & color );
	virtual void setRadius( float radius );
private:
	scene::ISceneManager * smgr;
	scene::ILightSceneNode * light;
};

class VideoSphereIrrLicht : public IVideoObject
{
public:
	VideoSphereIrrLicht(VS_VIDEO_OBJECT_ID id, scene::ISceneManager* nsmgr, irr::video::IVideoDriver * ndriver) : IVideoObject(id){ smgr = nsmgr; driver = ndriver; node = 0; }
	virtual ~VideoSphereIrrLicht(void);
	void create( VideoSimpleObjectCreateData data );
public:
	virtual void setPosition( vector3df & pos );
	virtual void setRotation( vector3df & rot );
	virtual void setScale( vector3df & scl );
	virtual vector3df getPosition();
	virtual vector3df getRotation();
	virtual vector3df getScale();

	virtual void remove();
	scene::IMeshSceneNode * getNode() {return node;}
protected:
	scene::ISceneManager * smgr;
	irr::video::IVideoDriver * driver;
	scene::IMeshSceneNode * node;
};

}