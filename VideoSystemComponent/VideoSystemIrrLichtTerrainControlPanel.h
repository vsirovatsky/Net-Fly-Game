#pragma once;

#include "VideoSystemTerrainControlPanel.h"
#include "VideoSystemIrrlichtManager.h"
#include <hash_map>

namespace videosystem {

class VideoSystemIrrLichtTerrainControlPanel : public VideoSystemTerrainControlPanel
{
public:
	VideoSystemIrrLichtTerrainControlPanel( VideoSystemIrrlichtManager * manager, irr::IrrlichtDevice * device, irr::video::IVideoDriver * driver, irr::scene::ISceneManager * smgr );
	virtual ~VideoSystemIrrLichtTerrainControlPanel(void);

	virtual VS_TERRAIN_INDEX createTerrainNode( TerrainCreateData & data );
	virtual void createSky( SkyCreateData & data );
	virtual void addTerrainNodeToCollision( VS_TERRAIN_INDEX index, vector3df userElipsoid );
private:
	VS_INT nextTerrainId;
	std::hash_map<VS_TERRAIN_INDEX, scene::ITerrainSceneNode*> terrainsHash;

	VideoSystemIrrlichtManager * manager;
	irr::IrrlichtDevice * device;
	irr::video::IVideoDriver * driver;
    irr::scene::ISceneManager * smgr;

	scene::ISceneNode* skydome;
	scene::ISceneNode* skybox;
};

}