#pragma once

#include "VideoSystemTypeDefs.h"

namespace videosystem {

class VideoSystemTerrainControlPanel
{
public:
	VideoSystemTerrainControlPanel(void){};
	virtual ~VideoSystemTerrainControlPanel(void){};

	virtual VS_TERRAIN_INDEX createTerrainNode( TerrainCreateData & data ) = 0;
	virtual void createSky( SkyCreateData & data ) = 0;
	virtual void addTerrainNodeToCollision( VS_TERRAIN_INDEX index, vector3df userElipsoid ) = 0;
};

}