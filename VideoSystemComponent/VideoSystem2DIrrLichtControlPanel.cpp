#include "StdAfx.h"
#include "VideoSystem2DIrrLichtControlPanel.h"

using namespace videosystem;
using namespace irr;

VideoSystem2DIrrLichtControlPanel::VideoSystem2DIrrLichtControlPanel( VideoSystemIrrlichtManager * _manager, irr::IrrlichtDevice * _device, irr::video::IVideoDriver * _driver, irr::scene::ISceneManager * _smgr ) : VideoSystem2DControlPanel()
{
	manager = _manager;
	device = _device;
	driver = _driver;
	smgr = _smgr;
}


VideoSystem2DIrrLichtControlPanel::~VideoSystem2DIrrLichtControlPanel(void)
{
}

void VideoSystem2DIrrLichtControlPanel::printText( VS_2D_ELEMENT_INDEX index, VS_STRING str )
{
	std::wstring w = std::wstring( str.begin(), str.end() );
	std::hash_map<VS_2D_ELEMENT_INDEX, gui::IGUIStaticText*>::iterator it = textsHash.find( index );
	if ( it == textsHash.end() ) {
		int nextPos = textsHash.size() * 20 + 10;
		gui::IGUIStaticText * t = device->getGUIEnvironment()->addStaticText(w.c_str(), core::rect<s32>(10, nextPos, 400, nextPos + 10));
		t->setOverrideColor(video::SColor(255, 255, 255, 0));
		textsHash.insert( std::pair<VS_2D_ELEMENT_INDEX, gui::IGUIStaticText*>(index,t) );
	} else {
		it->second->setText( w.c_str() );
	}
}
