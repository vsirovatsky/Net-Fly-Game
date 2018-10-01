#include "StdAfx.h"
#include "VideoSystemIrrlichtObjects.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

namespace videosystem {

	VideoObjectIrrlicht::~VideoObjectIrrlicht()
	{
		if ( node ) {
			node->remove();
			node = 0;
		}
	}

	void VideoObjectIrrlicht::create( VideoObjectCreateData data )
	{
		node = smgr->addMeshSceneNode(smgr->getMesh(data.file.c_str()),	0, getId());
		video::SMaterial material;
		if ( data.isTextured ) {
			material.setTexture(0, driver->getTexture(data.texture.c_str()));
		}
		material.Lighting = true;
		material.NormalizeNormals = true;
		node->getMaterial(0) = material;
	}

	void VideoObjectIrrlicht::setPosition( vector3df & pos )
	{
		node->setPosition(core::vector3df(pos.x,pos.y,pos.z));
	}

	void VideoObjectIrrlicht::setRotation( vector3df & rot )
	{
		node->setRotation(core::vector3df(rot.x,rot.y,rot.z));
	}

	void VideoObjectIrrlicht::setScale( vector3df & scl )
	{
		node->setScale(core::vector3df(scl.x,scl.y,scl.z));
	}

	vector3df VideoObjectIrrlicht::getPosition()
	{
		core::vector3df v = node->getPosition();
		return vector3df( v.X, v.Y, v.Z );
	}

	vector3df VideoObjectIrrlicht::getRotation()
	{
		core::vector3df v = node->getRotation();
		return vector3df( v.X, v.Y, v.Z );
	}

	vector3df VideoObjectIrrlicht::getScale()
	{
		core::vector3df v = node->getScale();
		return vector3df( v.X, v.Y, v.Z );
	}

	void VideoObjectIrrlicht::remove()
	{
		node->remove();
		node = 0;
	}
}



namespace videosystem {

	VideoAnimatedObjectIrrlicht::~VideoAnimatedObjectIrrlicht()
	{
		if ( node ) {
			node->remove();
			node = 0;
		}
	}

	void VideoAnimatedObjectIrrlicht::create( VideoObjectCreateData data )
	{
		node = smgr->addAnimatedMeshSceneNode(smgr->getMesh(data.file.c_str()),	0, getId());
		if ( data.isTextured ) {
			video::SMaterial material;
			material.setTexture(0, driver->getTexture(data.texture.c_str()));
			material.Lighting = true;
			material.NormalizeNormals = true;
			node->getMaterial(0) = material;
		} else if ( data.isMaterialized ) {
			node->getMaterial(0).NormalizeNormals = true;
		}
	}

	void VideoAnimatedObjectIrrlicht::setPosition( vector3df & pos )
	{
		node->setPosition(core::vector3df(pos.x,pos.y,pos.z));
	}

	void VideoAnimatedObjectIrrlicht::setRotation( vector3df & rot )
	{
		node->setRotation(core::vector3df(rot.x,rot.y,rot.z));
	}

	void VideoAnimatedObjectIrrlicht::setScale( vector3df & scl )
	{
		node->setScale(core::vector3df(scl.x,scl.y,scl.z));
	}

	vector3df VideoAnimatedObjectIrrlicht::getPosition()
	{
		core::vector3df v = node->getPosition();
		return vector3df( v.X, v.Y, v.Z );
	}

	vector3df VideoAnimatedObjectIrrlicht::getRotation()
	{
		core::vector3df v = node->getRotation();
		return vector3df( v.X, v.Y, v.Z );
	}

	vector3df VideoAnimatedObjectIrrlicht::getScale()
	{
		core::vector3df v = node->getScale();
		return vector3df( v.X, v.Y, v.Z );
	}

	void VideoAnimatedObjectIrrlicht::remove()
	{
		node->remove();
		node = 0;
	}

	void VideoAnimatedObjectIrrlicht::setAnimationSpead( VS_ANIMATION_SPEAD spead )
	{
		node->setAnimationSpeed( spead );
	}

	void VideoAnimatedObjectIrrlicht::setAnimationPosition( VS_ANIMATION_POSITION begin, VS_ANIMATION_POSITION end )
	{
		node->setFrameLoop( begin, end );
		node->setLoopMode( true );
	}

	void VideoAnimatedObjectIrrlicht::startAnimation()
	{
		// TODO: implement
	}

	void VideoAnimatedObjectIrrlicht::stopAnimation()
	{
		// TODO: implement
	}

}


namespace videosystem {

	void VideoCameraIrrlicht::setPosition( vector3df & pos )
	{
		camera->setPosition( core::vector3df(pos.x,pos.y,pos.z) );
	}

	void VideoCameraIrrlicht::setTarget( vector3df & tar )
	{
		camera->setTarget( core::vector3df(tar.x,tar.y,tar.z) );
	}

	void VideoCameraIrrlicht::create()
	{
		camera = smgr->addCameraSceneNodeFPS(0, 100.0f, .3f, 0, 0, 0, true, 3.f);
		camera->setFarValue(42000.0f);
		//camera = smgr->addCameraSceneNode();
		//camera->bindTargetAndRotation( true );
	}

	vector3df VideoCameraIrrlicht::getRotaition()
	{
		core::vector3df pos = camera->getAbsolutePosition();
		core::vector3df target = camera->getTarget();
		core::vector3df dir = target - pos; 
		core::vector3df rotation = dir.normalize();//.getHorizontalAngle();   
		return vector3df(rotation.X, rotation.Y, rotation.Z);
	}

	vector3df VideoCameraIrrlicht::getPosition()
	{
		core::vector3df v = camera->getPosition();
		return vector3df(v.X, v.Y, v.Z);
	}

}

namespace videosystem {

	VideoLightIrrlicht::~VideoLightIrrlicht()
	{
		if ( light ) {
			light->remove();
			light = 0;
		}
	}

	void VideoLightIrrlicht::create()
	{
		light = smgr->addLightSceneNode();
	}

	void VideoLightIrrlicht::setPosition( vector3df & pos )
	{
		light->setPosition( core::vector3df(pos.x,pos.y,pos.z) );
	}

	void VideoLightIrrlicht::setColor( color4d & color )
	{
		light->getLightData().AmbientColor.r = color.red;
		light->getLightData().AmbientColor.g = color.green;
		light->getLightData().AmbientColor.b = color.blue;
		light->getLightData().AmbientColor.a = color.alfa;
	}

	void VideoLightIrrlicht::setRadius( float radius )
	{
		light->setRadius( radius );
	}

}

namespace videosystem {

	VideoSphereIrrLicht::~VideoSphereIrrLicht()
	{
		if ( node ) {
			node->remove();
			node = 0;
		}
	}
	
	void VideoSphereIrrLicht::create( VideoSimpleObjectCreateData data )
	{
		node = smgr->addSphereSceneNode( data.radius, data.polynum, 0, getId() );
		if ( data.isTextured ) {
			node->setMaterialTexture(0, driver->getTexture( data.textureFile.c_str() ));
		}
		node->setMaterialFlag(video::EMF_LIGHTING, true);
	}

	void VideoSphereIrrLicht::setPosition( vector3df & pos )
	{
		node->setPosition(core::vector3df(pos.x,pos.y,pos.z));
	}

	void VideoSphereIrrLicht::setRotation( vector3df & rot )
	{
		node->setRotation(core::vector3df(rot.x,rot.y,rot.z));
	}

	void VideoSphereIrrLicht::setScale( vector3df & scl )
	{
		node->setScale(core::vector3df(scl.x,scl.y,scl.z));
	}

	vector3df VideoSphereIrrLicht::getPosition()
	{
		core::vector3df v = node->getPosition();
		return vector3df( v.X, v.Y, v.Z );
	}

	vector3df VideoSphereIrrLicht::getRotation()
	{
		core::vector3df v = node->getRotation();
		return vector3df( v.X, v.Y, v.Z );
	}

	vector3df VideoSphereIrrLicht::getScale()
	{
		core::vector3df v = node->getScale();
		return vector3df( v.X, v.Y, v.Z );
	}

	void VideoSphereIrrLicht::remove()
	{
		node->remove();
		node = 0;
	}
}