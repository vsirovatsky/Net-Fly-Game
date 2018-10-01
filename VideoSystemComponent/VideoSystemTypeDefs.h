#pragma once

#include "stdafx.h"

#include <iostream>

#define VS_STRING std::string
#define VS_INT int
#define VS_VIDEO_OBJECT_ID long

#define VS_ANIMATION_SPEAD float
#define VS_ANIMATION_POSITION int

#define VS_SIMPLE_FLOAT float
#define VS_SIMPLE_INT int

#define VS_TERRAIN_INDEX unsigned int
#define VS_2D_ELEMENT_INDEX unsigned int

namespace videosystem {

enum VS_SIMPLE_OBJECT_TYPES {
	VS_SIMPLE_OBJECT_TYPE_SPHERE = 0
};

enum VS_COLOR_DEPTH {
	VS_COLOR_16 = 16,
	VS_COLOR_32 = 32
};

enum VS_DRIVER_TYPE
{
	//! Null driver, useful for applications to run the engine without visualisation.
	/** The null device is able to load textures, but does not
	render and display any graphics. */
	VS_DT_NULL = 0,

	//! The Irrlicht Engine Software renderer.
	/** Runs on all platforms, with every hardware. It should only
	be used for 2d graphics, but it can also perform some primitive
	3d functions. These 3d drawing functions are quite fast, but
	very inaccurate, and don't even support clipping in 3D mode. */
	VS_DT_SOFTWARE,

	//! The Burning's Software Renderer, an alternative software renderer
	/** Basically it can be described as the Irrlicht Software
	renderer on steroids. It rasterizes 3D geometry perfectly: It
	is able to perform correct 3d clipping, perspective correct
	texture mapping, perspective correct color mapping, and renders
	sub pixel correct, sub texel correct primitives. In addition,
	it does bilinear texel filtering and supports more materials
	than the EDT_SOFTWARE driver. This renderer has been written
	entirely by Thomas Alten, thanks a lot for this huge
	contribution. */
	VS_DT_BURNINGSVIDEO,

	//! Direct3D8 device, only available on Win32 platforms.
	/** Performs hardware accelerated rendering of 3D and 2D
	primitives. */
	VS_DT_DIRECT3D8,

	//! Direct3D 9 device, only available on Win32 platforms.
	/** Performs hardware accelerated rendering of 3D and 2D
	primitives. */
	VS_DT_DIRECT3D9,

	//! OpenGL device, available on most platforms.
	/** Performs hardware accelerated rendering of 3D and 2D
	primitives. */
	VS_DT_OPENGL,

	//! No driver, just for counting the elements
	VS_DT_COUNT
};

struct VS_Context 
{
public:
	VS_Context() : driverType(VS_DT_SOFTWARE), width(640), height(480),
			colorDepth(VS_COLOR_32), fullscreen(false), stencilbuffer(false), 
			vsync(false),  videoSystemToCaptureEvents(false) {
	}
	VS_Context( VS_DRIVER_TYPE nDriverType, VS_INT nWidth, VS_INT nHeight ) : driverType(nDriverType), 
			width(nWidth), height(nHeight),
			colorDepth(VS_COLOR_32), fullscreen(false), stencilbuffer(false), 
			vsync(false),  videoSystemToCaptureEvents(false) {
	}
	VS_DRIVER_TYPE driverType;
	VS_INT width;
	VS_INT height;
	VS_COLOR_DEPTH colorDepth;
	bool fullscreen;
	bool stencilbuffer;
	bool vsync;
	bool videoSystemToCaptureEvents;
	bool cursorVisible;

};

struct color4d
{
	color4d() : red(0), green(0), blue(0), alfa(0) {}
	color4d(float nred, float ngreen, float nblue, float nalfa) : red(nred), green(ngreen), blue(nblue), alfa(nalfa) {}
	color4d( color4d & other ) : red(other.red), green(other.green), blue(other.blue), alfa(other.alfa) {}
	// All should be between 0.0f and 1.0f
	float red;
	float green;
	float blue;
	float alfa;
};

struct vector3df
{
public:
	vector3df() : x(0), y(0), z(0) {}
	vector3df(float nx, float ny, float nz) : x(nx), y(ny), z(nz) {}
	vector3df( vector3df & other ) : x(other.x), y(other.y), z(other.z) {}
	float length(){ return std::sqrt(x*x + y*y + z*z);}
	bool equals( vector3df & other ){ return ((other.x==x)&&(other.y==y)&&(other.z==z));}
	float x;
	float y;
	float z;
};

struct VideoObjectCreateData {
public:
	VS_VIDEO_OBJECT_ID id;
	VS_STRING file;
	bool isTextured;
	bool isMaterialized;
	VS_STRING texture;
	VS_INT material;
};

struct VideoSimpleObjectCreateData {
public:
	VS_SIMPLE_OBJECT_TYPES type;
	VS_VIDEO_OBJECT_ID id;
	VS_SIMPLE_FLOAT radius;
	VS_SIMPLE_INT polynum;
	VS_STRING textureFile;
	bool isTextured;
};

struct TerrainCreateData {
	TerrainCreateData( VS_TERRAIN_INDEX _index ) : index(_index), position(0.0f,0.0f,0.0f), rotaition(0.0f,0.0f,0.0f), scale(1.0f,1.0f,1.0f), parentTerrain(0){
		terrainHeightmapFile = 0;
		terrainFirstTextureFile = 0;
		terrainSecondTextureFile = 0;
	};
	TerrainCreateData( VS_TERRAIN_INDEX _index, VS_SIMPLE_FLOAT posX, VS_SIMPLE_FLOAT posY, VS_SIMPLE_FLOAT posZ ) : index(_index), position(posX,posY,posZ), rotaition(0.0f,0.0f,0.0f), scale(1.0f,1.0f,1.0f), parentTerrain(0){
		terrainHeightmapFile = 0;
		terrainFirstTextureFile = 0;
		terrainSecondTextureFile = 0;
	};
	TerrainCreateData( VS_TERRAIN_INDEX _index, VS_SIMPLE_FLOAT posX, VS_SIMPLE_FLOAT posY, VS_SIMPLE_FLOAT posZ, VS_SIMPLE_FLOAT scaleX, VS_SIMPLE_FLOAT scaleY, VS_SIMPLE_FLOAT scaleZ ) : index(_index), position(posX,posY,posZ), rotaition(0.0f,0.0f,0.0f), scale(scaleX,scaleY,scaleZ), parentTerrain(0) {
		terrainHeightmapFile = 0;
		terrainFirstTextureFile = 0;
		terrainSecondTextureFile = 0;
	};
	VS_STRING * terrainHeightmapFile;
	VS_STRING * terrainFirstTextureFile;
	VS_STRING * terrainSecondTextureFile;
	VS_TERRAIN_INDEX index;
	VS_TERRAIN_INDEX parentTerrain;
	vector3df position;
	vector3df rotaition;
	vector3df scale;
	VS_SIMPLE_FLOAT firstTerrainScale;
	VS_SIMPLE_FLOAT secondTerrainScale;
};

struct SkyCreateData {
	// Sky Box by default
	SkyCreateData() : useSkyBox(true) {}
	SkyCreateData( bool _useSkyBox ) : useSkyBox(_useSkyBox) {}
	bool useSkyBox;
	VS_STRING * skyBox_Up;
	VS_STRING * skyBox_Down;
	VS_STRING * skyBox_Left;
	VS_STRING * skyBox_Right;
	VS_STRING * skyBox_Forward;
	VS_STRING * skyBox_Back;
	VS_STRING * skyDom;
};

class IVideoObject 
{
public:
	IVideoObject( VS_VIDEO_OBJECT_ID id ) : m_id(id) {}
	virtual ~IVideoObject(){}
	VS_VIDEO_OBJECT_ID & getId(){return m_id;}

	virtual void setPosition( vector3df & pos ) = 0;
	virtual void setRotation( vector3df & rot ) = 0;
	virtual void setScale( vector3df & scl ) = 0;
	virtual vector3df getPosition() = 0;
	virtual vector3df getRotation() = 0;
	virtual vector3df getScale() = 0;

	virtual void remove() = 0;
private:
	VS_VIDEO_OBJECT_ID m_id;
};

class IVideoAnimatedObject : public IVideoObject
{
public:
	IVideoAnimatedObject( VS_VIDEO_OBJECT_ID id ) : IVideoObject(id) {}
	virtual void setAnimationSpead( VS_ANIMATION_SPEAD spead ) = 0;
	virtual void setAnimationPosition( VS_ANIMATION_POSITION begin, VS_ANIMATION_POSITION end ) = 0;
	virtual void startAnimation() = 0;
	virtual void stopAnimation() = 0;
};

class IVideoCamera 
{
public:
	IVideoCamera(){}
	virtual void setPosition( vector3df & pos ) = 0;
	virtual void setTarget( vector3df & pos ) = 0;
	virtual vector3df getRotaition() = 0;
	virtual vector3df getPosition() = 0;
};

class ILight
{
public:
	ILight(){}
	virtual ~ILight(){}
	virtual void setPosition( vector3df & pos ) = 0;
	virtual void setColor( color4d & color ) = 0;
	virtual void setRadius( float radius ) = 0;
private:
	VS_VIDEO_OBJECT_ID m_id;
};

}