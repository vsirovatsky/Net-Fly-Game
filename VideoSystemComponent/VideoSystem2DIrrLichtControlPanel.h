#pragma once

#include "Logger.h"
#include "VideoSystem2DControlPanel.h"
#include "VideoSystemIrrlichtManager.h"
#include <hash_map>

namespace videosystem {

class VideoSystem2DIrrLichtControlPanel : public VideoSystem2DControlPanel
{
public:
	VideoSystem2DIrrLichtControlPanel( VideoSystemIrrlichtManager * , irr::IrrlichtDevice * , irr::video::IVideoDriver * , irr::scene::ISceneManager * );
	virtual ~VideoSystem2DIrrLichtControlPanel(void);

	virtual void printText( VS_2D_ELEMENT_INDEX index, VS_STRING str );
private:
	VideoSystemIrrlichtManager * manager;
	irr::IrrlichtDevice * device;
	irr::video::IVideoDriver * driver;
    irr::scene::ISceneManager * smgr;

	std::hash_map<VS_2D_ELEMENT_INDEX, gui::IGUIStaticText*> textsHash;
};

}