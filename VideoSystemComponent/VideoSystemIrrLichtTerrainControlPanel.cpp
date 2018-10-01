#include "StdAfx.h"
#include "VideoSystemIrrLichtTerrainControlPanel.h"
#include "VideoSystemException.h"

using namespace videosystem;
using namespace irr;

VideoSystemIrrLichtTerrainControlPanel::VideoSystemIrrLichtTerrainControlPanel( VideoSystemIrrlichtManager * _manager, irr::IrrlichtDevice * _device, irr::video::IVideoDriver * _driver, irr::scene::ISceneManager * _smgr ) : VideoSystemTerrainControlPanel()
{
	manager = _manager;
	device = _device;
	driver = _driver;
	smgr = _smgr;
}


VideoSystemIrrLichtTerrainControlPanel::~VideoSystemIrrLichtTerrainControlPanel(void)
{
}

VS_TERRAIN_INDEX VideoSystemIrrLichtTerrainControlPanel::createTerrainNode( TerrainCreateData & data )
{
	if ( data.terrainHeightmapFile == 0 ) {
		throw VideoSystemNoResourceException("No HeightmapFile provided on Terrain node creation");
	}
	try {
		scene::ITerrainSceneNode* terrain = smgr->addTerrainSceneNode(
			data.terrainHeightmapFile->c_str(),
			0,					// parent node IMPLEMENT
			-1,					// node id
			core::vector3df(data.position.x, data.position.y, data.position.z),		// position
			core::vector3df(data.rotaition.x, data.rotaition.y, data.rotaition.z),		// rotation
			core::vector3df(data.scale.x, data.scale.y, data.scale.z),	// scale
			video::SColor ( 255, 255, 255, 255 ),	// vertexColor
			5,					// maxLOD
			scene::ETPS_17,				// patchSize
			4					// smoothFactor
			);
		terrain->setMaterialFlag(video::EMF_LIGHTING, false);

		if ( (data.terrainFirstTextureFile != 0) && (data.terrainSecondTextureFile != 0) ) {
			terrain->setMaterialTexture(0,
				driver->getTexture(data.terrainFirstTextureFile->c_str()));
			terrain->setMaterialTexture(1,
				driver->getTexture(data.terrainSecondTextureFile->c_str()));
			terrain->setMaterialType(video::EMT_DETAIL_MAP);
			terrain->scaleTexture(data.firstTerrainScale, data.secondTerrainScale);
		} else if ( (data.terrainFirstTextureFile != 0) ) {
			terrain->setMaterialTexture(0,
				driver->getTexture(data.terrainFirstTextureFile->c_str()));
			terrain->setMaterialType(video::EMT_DETAIL_MAP);
			terrain->scaleTexture(data.firstTerrainScale);
		}
		terrainsHash.insert( std::pair<VS_INT, scene::ITerrainSceneNode*>( data.index, terrain ) );
	} catch (...) {
		throw VideoSystemException("Error in creating Terrain node");
	}
}

void VideoSystemIrrLichtTerrainControlPanel::createSky( SkyCreateData & data )
{
	driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, false);
	if ( data.useSkyBox ) {
		skybox = smgr->addSkyBoxSceneNode(
			driver->getTexture( data.skyBox_Up->c_str() ),
			driver->getTexture( data.skyBox_Down->c_str() ),
			driver->getTexture( data.skyBox_Left->c_str() ),
			driver->getTexture( data.skyBox_Right->c_str() ),
			driver->getTexture( data.skyBox_Forward->c_str() ),
			driver->getTexture( data.skyBox_Back->c_str() ) );
	} else {
		skydome = smgr->addSkyDomeSceneNode(driver->getTexture( data.skyDom->c_str() ),16,8,0.95f,2.0f);
	}
	driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, true);
}

void VideoSystemIrrLichtTerrainControlPanel::addTerrainNodeToCollision( VS_TERRAIN_INDEX index, vector3df userElipsoid )
{
	scene::ITerrainSceneNode* terrain = terrainsHash[index];
	if ( terrain==0 ) {
		throw VideoSystemException("index not found");
	}
	scene::ITriangleSelector* selector = smgr->createTerrainTriangleSelector(terrain, 0);
	terrain->setTriangleSelector(selector);

	// create collision response animator and attach it to the camera
	scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
		selector, manager->getCamera()->getCameraNode(), core::vector3df(userElipsoid.x,userElipsoid.y,userElipsoid.z),
		core::vector3df(0,-10.0f,0),
		core::vector3df(0,50,0));
	selector->drop();
	manager->getCamera()->getCameraNode()->addAnimator(anim);
	anim->drop();

}